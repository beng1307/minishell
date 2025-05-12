/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:27 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/02 20:11:21 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_function(t_minishell *shell, pid_t pid, int *fd)
{
	int	return_value;

	if (shell->exec->loop == (shell->exec->cmd_count - 1)
		|| shell->exec->redir_flag == true)
	{
		shell->exec->redir_flag = false;
		close(fd[0]);
		while (true)
		{
			return_value = wait(&shell->exec->exit_status);
			if (return_value == pid || return_value == -1)
				break ;
		}
		while (wait(NULL) != -1)
			;
		if (WIFSIGNALED(shell->exec->exit_status))
			shell->exitcode = 128 + WTERMSIG(shell->exec->exit_status);
		else if (WIFEXITED(shell->exec->exit_status))
			shell->exitcode = WEXITSTATUS(shell->exec->exit_status);
		if (shell->exitcode == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (shell->exitcode >= 130)
			ft_putstr_fd("\n", 2);
	}
}
