/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execute_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:39 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 22:31:00 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_execve(t_minishell *shell, char *path)
{
	errno = 0;
	execve(path, shell->exec->args, shell->exec->envp);
	perror(path);
	if (errno == EACCES)
		shell->exitcode = 126;
	else
		shell->exitcode = 127;
	if (shell->exec->check != 222)
		ft_free(&path);
	shell->called_from_exit = true;
	return (free_all_exec(shell, 1), terminator(), 1);
}

void	relative_absolute_path(t_minishell *shell, char **path, int index)
{
	(*path) = shell->exec->args[index];
	directory_check(shell, (*path));
	shell->exec->check = 222;
}

int	arg_index(t_minishell *shell)
{
	int	index;

	index = 0;
	while (shell->exec->args[index] && !shell->exec->args[index][0]
			&& index < shell->exec->cmd_count)
		index++;
	return (index);
}

void	exit_no_args(t_minishell *shell)
{
	if (shell->exec->args[0] && ft_strlen(shell->exec->args[0]) == 0)
		error_message(shell, ": command not found\n", 127);
	free_all_exec(shell, 1);
	set_exit_flag(shell);
	terminator();
}

int	execute(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	char		*path;
	t_tokens	*tok_cpy;
	int			index;

	tok_cpy = tokens;
	index = 0;
	path = NULL;
	while (tok_cpy && ft_strcmp(tok_cpy->token, shell->exec->args[0]) != 0)
		tok_cpy = tok_cpy->next;
	if (buildin_commands_exec(shell, tokens, env, shell->exec->args[0]) == 0)
	{
		if (!shell->exec->args || !*shell->exec->args[0])
			return (exit_no_args(shell), 0);
		dot_cases(shell, index);
		if (check_for_slash(shell->exec->args, index) == 1)
			relative_absolute_path(shell, &path, index);
		else
			path = find_path_command(shell, shell->exec->args[index]);
		if (!path)
			exit_execution(shell, path, index);
		return (signal(SIGQUIT, SIG_DFL),
			signal(SIGINT, SIG_DFL), call_execve(shell, path));
	}
	return (set_exit_flag(shell), free_all_exec(shell, 1), terminator(), 0);
}
