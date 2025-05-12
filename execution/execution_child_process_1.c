/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:19 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 17:26:09 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_2_infile_process(t_minishell *shell, int *fd)
{
	if (shell->exec->infile != -1)
	{
		if (dup2(shell->exec->infile, STDIN_FILENO) == -1)
			return (perror("dup2, infile"), free_all_exec(shell, 1),
				set_exit_flag(shell), my_close(fd, shell), terminator());
		close(shell->exec->infile);
		shell->exec->infile = -1;
		if (shell->exec->prev_fd != -1)
		{
			close(shell->exec->prev_fd);
			shell->exec->prev_fd = -1;
		}
	}
	else if (shell->exec->loop > 0 && shell->exec->prev_fd != -1)
	{
		if (dup2(shell->exec->prev_fd, STDIN_FILENO) == -1)
			return (perror("dup2, connect"), free_all_exec(shell, 1),
				set_exit_flag(shell), my_close(fd, shell), terminator());
		close(shell->exec->prev_fd);
		shell->exec->prev_fd = -1;
	}
}

void	dup_2_outfile_process(t_minishell *shell, int *fd)
{
	if (shell->exec->outfile != -1)
	{
		if (dup2(shell->exec->outfile, STDOUT_FILENO) == -1)
			return (close(fd[1]), perror("dup2, out"), free_all_exec(shell,
					1), set_exit_flag(shell), my_close(fd, shell),
				terminator());
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	else if (shell->exec->loop < (shell->exec->cmd_count - 1))
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 fd[1]"), free_all_exec(shell, 1),
				set_exit_flag(shell), my_close(fd, shell), terminator());
	}
	if (shell->exec->prev_fd != -1)
	{
		close(shell->exec->prev_fd);
		shell->exec->prev_fd = -1;
	}
	close(fd[1]);
}

void	parent_process(t_minishell *shell, pid_t pid, int *fd)
{
	if (shell->exec->prev_fd != -1 && shell->exec->prev_fd != fd[0])
		close(shell->exec->prev_fd);
	shell->exec->prev_fd = fd[0];
	my_close(fd, shell);
	if (shell->exec->args)
		free_array(&shell->exec->args);
	shell->exec->pid = pid;
	wait_function(shell, pid, fd);
}

void	close_prev(t_minishell *shell)
{
	if (shell->exec->prev_fd != -1)
	{
		close(shell->exec->prev_fd);
		shell->exec->prev_fd = -1;
	}
}

int	child_process(t_minishell *shell, t_cmd *cmd, t_tokens *tokens, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd_cpy;

	cmd_cpy = cmd;
	shell->exec->args = set_args(shell, cmd_cpy);
	if (shell->exec->args == NULL)
		return (error_message(shell, "ALLOCATION ERROR", 1), 1);
	if (get_infile_outfile(shell, cmd_cpy, env) == -1)
		return (free_array(&shell->exec->args),
			wait_out_of_gio(), close_prev(shell), 0);
	if (pipe(fd) == -1)
		return (free_all_exec(shell, 1), terminator(), 1);
	pid = fork();
	if (pid == -1)
		return (free_all_exec(shell, 1), close(fd[0]), my_close(fd, shell),
			terminator(), 1);
	if (pid == 0)
		return (close(fd[0]),
			dup_2_infile_process(shell, fd),
			dup_2_outfile_process(shell, fd), execute(shell, tokens, env));
	else
		return (ignore_signals(), parent_process(shell, pid, fd), 999);
	return (0);
}
