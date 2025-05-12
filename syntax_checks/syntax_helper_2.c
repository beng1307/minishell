/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:09 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:10 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_append_inp_helper(t_minishell *shell, int i)
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
	}
}

void	check_heredoc_inp_helper(t_minishell *shell, int i)
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
	}
}

void	check_out_inp_helper(t_minishell *shell, int i)
{
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '<')
	{
		shell->error->e = i;
		if (shell->input[i + 1] != '\0'
			&& shell->input[i] == shell->input[i + 1])
			shell->is_here_app = 1;
	}
}

void	check_in_inp_helper(t_minishell *shell, int i)
{
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '>')
	{
		shell->error->e = i;
		if (shell->input[i + 1] != '\0'
			&& shell->input[i] == shell->input[i + 1])
			shell->is_here_app = 1;
	}
}
