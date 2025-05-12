/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:15 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/02 22:51:49 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_count(t_cmd_table *cmd_table)
{
	t_cmd_table	*cmd_cpy;
	t_cmd		*cmd;
	int			count;

	cmd_cpy = cmd_table;
	count = 0;
	while (cmd_cpy)
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == COMMAND)
			{
				count++;
				break ;
			}
			cmd = cmd->next;
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (count);
}

int	redir_count(t_cmd_table *cmd_table)
{
	t_cmd_table	*cmd_cpy;
	t_cmd		*cmd;
	int			count;

	cmd_cpy = cmd_table;
	count = 0;
	while (cmd_cpy)
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == INPUT || cmd->type == OUTPUT || cmd->type == APPEND
				|| cmd->type == HEREDOC)
				count++;
			cmd = cmd->next;
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (count);
}

int	execute_single_redir(t_minishell *shell, t_env *env)
{
	shell->exec->cmd = shell->exec->cmd_cpy->cmd;
	shell->exitcode = 0;
	free_array(&shell->exec->envp);
	get_infile_outfile(shell, shell->exec->cmd, env);
	return (0);
}

// void	wait_function_last_redir(t_minishell *shell)
// {
// 	int	return_value;

// 		while (true)
// 		{
// 			return_value = wait(&shell->exec->exit_status);
// 			if (return_value == shell->exec->pid || return_value == -1)
// 				break ;
// 		}
// 		while (wait(NULL) != -1)
// 			;
// 		if (WIFEXITED(shell->exec->exit_status))
// 			shell->exitcode = WEXITSTATUS(shell->exec->exit_status);
// }

int	execute_redir(t_minishell *shell, t_env *env)
{
	get_infile_outfile(shell, shell->exec->cmd, env);
	shell->fu_dog_goat = true;
	my_close_main_exec(shell);
	shell->exec->loop++;
	if (shell->exec->crnt_token->next)
		shell->exec->crnt_token = shell->exec->crnt_token->next;
	return (0);
}

void	set_fu_dog(t_minishell *shell)
{
	shell->fu_dog_goat = true;
}
