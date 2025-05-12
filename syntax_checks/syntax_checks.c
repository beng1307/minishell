/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:05 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:06 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_check_inp(t_minishell *shell, int i, int j)
{
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '>'
			|| shell->input[i] == '<')
		{
			shell->error->e = i;
			if (shell->input[i + 1] != '\0'
				&& shell->input[i] == shell->input[i + 1])
				shell->is_here_app = 1;
			return ;
		}
		i = j + 1;
	}
	if (helper_in(shell, i, j) == 1)
		return ;
	check_in_inp_helper(shell, i);
}

void	out_check_inp(t_minishell *shell, int i, int j)
{
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			if (shell->input[i + 1] != '\0'
				&& shell->input[i] == shell->input[i + 1])
				shell->is_here_app = 1;
			return ;
		}
		i = j + 1;
	}
	if (helper_out(shell, i, j) == 1)
		return ;
	check_out_inp_helper(shell, i);
}

void	pipe_check_inp(t_minishell *shell, int i, int j)
{
	if (j == -1)
	{
		shell->error->e = i;
		return ;
	}
	if (helper_pipe(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|')
		shell->error->e = i;
}

void	append_check_inp(t_minishell *shell, int i, int j)
{
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			if (shell->input[i + 1] != '\0'
				&& shell->input[i] == shell->input[i + 1])
				shell->is_here_app = 1;
			return ;
		}
		i = j + 2;
	}
	if (helper_app_here(shell, i, j) == 1)
		return ;
	check_append_inp_helper(shell, i);
}

void	heredoc_check_inp(t_minishell *shell, int i, int j)
{
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			if (shell->input[i + 1] != '\0'
				&& shell->input[i] == shell->input[i + 1])
				shell->is_here_app = 1;
			return ;
		}
		i = j + 2;
	}
	if (helper_app_here(shell, i, j) == 1)
		return ;
	check_heredoc_inp_helper(shell, i);
}
