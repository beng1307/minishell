/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_free_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:47 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/02 22:51:26 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envp(t_minishell *shell)
{
	if (shell->exec->envp || *shell->exec->envp)
		free_array(&shell->exec->envp);
}

void	free_args(t_minishell *shell)
{
	int	i;

	i = 0;
	if (!shell->exec->args || !*shell->exec->args)
		return ;
	while (shell->exec->args[i] != NULL)
	{
		ft_free(&(shell->exec->args[i]));
		i++;
	}
}

void	exit_execution(t_minishell *shell, char *path, int index)
{
	path = shell->exec->args[index];
	ft_putstr_fd(path, 2);
	write(2, ": command not found\n", 20);
	if (shell->exec->to_free_exec == true)
	{
		free_array(&shell->exec->args);
		free_array(&shell->exec->envp);
	}
	shell->called_from_exit = true;
	shell->exitcode = 127;
	terminator();
}

void	close_heredoc(t_minishell *shell)
{
	close(shell->exec->infile);
	shell->exec->infile = -1;
}
