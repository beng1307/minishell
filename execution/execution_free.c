/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:52 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/02 22:49:47 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_close_buildin(t_minishell *shell, int *std)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	if (std[0] != -1)
		close(std[0]);
	if (std[1] != -1)
		close(std[1]);
}

void	my_close(int *fd, t_minishell *shell)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
}

void	free_array(char ***array)
{
	int	i;

	i = 0;
	if (!*array)
		return ;
	while ((*array)[i] != NULL)
	{
		ft_free(&((*array)[i]));
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_all_exec(t_minishell *shell, int check)
{
	if (shell->exec->path && *shell->exec->path)
		ft_free(&shell->exec->path);
	if (shell->exec->path_split && *shell->exec->path_split)
		free_array(&shell->exec->path_split);
	if (check != 0 && (shell->exec->envp && *shell->exec->envp))
		free_array(&shell->exec->envp);
	if (check != 0 && (shell->exec->args && *shell->exec->args))
		free_array(&shell->exec->args);
}

void	my_close_main_exec(t_minishell *shell)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	if (shell->exec->prev_fd != -1)
	{
		if (shell->exec->loop > 0)
			close(shell->exec->prev_fd);
		shell->exec->prev_fd = -1;
	}
}
