/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:37 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 17:42:16 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	directory_check(t_minishell *shell, char *path)
{
	DIR	*directory;

	errno = 0;
	directory = opendir(path);
	if (directory == NULL)
	{
		if (errno == EACCES)
		{
			shell->called_from_exit = true;
			shell->exitcode = 126;
			return (ft_putstr_fd(path, 2), write(2, ": Is a directory\n", 17),
				free_all_exec(shell, 1), terminator());
		}
		return ;
	}
	if (errno == ENOTDIR)
	{
		return ;
	}
	closedir(directory);
	shell->called_from_exit = true;
	shell->exitcode = 126;
	return (ft_putstr_fd(path, 2), write(2, ": Is a directory\n", 17),
		free_all_exec(shell, 1), terminator());
}

void	set_shell_exec_variables(t_minishell *shell, t_cmd_table *cmd_table,
	t_tokens *tokens, t_env *env)
{
	shell->exec->crnt_token = tokens;
	shell->exec->cmd_cpy = cmd_table;
	shell->exec->cmd_count = command_count(cmd_table);
	shell->exec->redir_count = redir_count(cmd_table);
	shell->exec->justr_count = just_redir_count(shell, cmd_table, false, 0);
	shell->exec->cmd_count += shell->exec->justr_count;
	shell->exec->envp = copy_envp(env);
	shell->exec->loop = 0;
}

int	execute_simple_command(t_minishell *shell,
	t_cmd_table *cmd_table, t_env *env)
{
	while (shell->exec->crnt_token && ft_strcmp(shell->exec->crnt_token->token,
			shell->exec->cmd->command[0]) != 0)
		shell->exec->crnt_token = shell->exec->crnt_token->next;
	if ((shell->exec->cmd_count == 1)
		&& shell->exec->redir_count == 0 && (is_there_a_pipe(cmd_table) == 0)
		&& (is_buildin(shell->exec->cmd->command[0]) == 1))
		return (free_array(&shell->exec->envp),
			buildin_commands(shell, shell->exec->crnt_token, env,
				shell->exec->cmd->command[0]), 0);
	if (shell->exec->cmd_count == 1 && shell->exec->redir_count != 0
		&& is_buildin(shell->exec->cmd->command[0]) == 1
		&& is_there_a_pipe(cmd_table) == 0)
	{
		free_envp(shell);
		shell->exec->cmd = shell->exec->cmd_cpy->cmd;
		if (buildin_process(shell, shell->exec->crnt_token,
				env, shell->exec->cmd) == 1)
			return (perror("ERROR_BUILDIN_PROCESS"), 1);
		return (0);
	}
	shell->exec->cmd = shell->exec->cmd_cpy->cmd;
	if (child_process(shell, shell->exec->cmd,
			shell->exec->crnt_token, env) == 1)
		return (free_envp(shell), 1);
	return (set_fu_dog(shell), 999);
}

int	execute_main_loop(t_minishell *shell, t_cmd_table *cmd_table, t_env *env)
{
	while (shell->exec->cmd)
	{
		if (how_many_cmds(shell->exec->cmd) == 0
			&& shell->exec->cmd->type != COMMAND)
		{
			execute_redir(shell, env);
			break ;
		}
		if (shell->exec->cmd->type == COMMAND)
		{
			if (execute_simple_command(shell, cmd_table, env) != 999)
				return (1);
			if (shell->exec->crnt_token->next)
				shell->exec->crnt_token = shell->exec->crnt_token->next;
			shell->exec->loop++;
			break ;
		}
		shell->exec->cmd = shell->exec->cmd->next;
	}
	return (0);
}

int	execute_commands(t_minishell *shell, t_tokens *tokens, t_env *env,
		t_cmd_table *cmd_table)
{
	set_shell_exec_variables(shell, cmd_table, tokens, env);
	if (shell->exec->cmd_count == 0 && shell->exec->redir_count >= 1)
		return (execute_single_redir(shell, env), 0);
	while (shell->exec->cmd_cpy
		&& shell->exec->loop < ((shell->exec->cmd_count)))
	{
		shell->exec->cmd = shell->exec->cmd_cpy->cmd;
		if (execute_main_loop(shell, cmd_table, env) == 1)
			return (1);
		shell->exec->cmd_cpy = shell->exec->cmd_cpy->next;
	}
	return (free_envp(shell), 0);
}
