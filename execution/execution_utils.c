/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:24 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 17:00:17 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_function(t_minishell *shell, t_cmd *cmd, t_env *env)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (ft_strncmp(cmd->redir[0], "<<", 2) == 0)
	{
		if (heredoc(cmd, shell, env) == 1)
			return (ft_free(&shell->exec->heredoc), -1);
		ft_free(&shell->exec->heredoc);
	}
	return (0);
}

int	input_function(t_minishell *shell, t_cmd *cmd)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (ft_strncmp(cmd->redir[0], "<", 1) == 0)
		if (input(cmd, shell) == 1)
			return (-1);
	return (0);
}

int	output_function(t_minishell *shell, t_cmd *cmd)
{
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	if (ft_strncmp(cmd->redir[0], ">", 1) == 0)
		if (output(cmd, shell) == 1)
			return (-1);
	return (0);
}

int	append_function(t_minishell *shell, t_cmd *cmd)
{
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	if (ft_strncmp(cmd->redir[0], ">>", 2) == 0)
		if (append(cmd, shell) == 1)
			return (-1);
	return (0);
}

int	get_infile_outfile(t_minishell *shell, t_cmd *cmd, t_env *env)
{
	while (cmd)
	{
		if (cmd->type == HEREDOC)
		{
			if (heredoc_function(shell, cmd, env) == -1)
				return (-1);
		}
		if (cmd->type == INPUT)
		{
			if (input_function(shell, cmd) == -1)
				return (-1);
		}
		if (cmd->type == OUTPUT)
		{
			if (output_function(shell, cmd) == -1)
				return (-1);
		}
		if (cmd->type == APPEND)
		{
			if (append_function(shell, cmd) == -1)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}
