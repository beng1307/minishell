/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:21 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:22 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_whitespaces(t_minishell *shell, int i)
{
	while (shell->input[i] == ' ' || shell->input[i] == '\t')
		i++;
	return (i);
}

int	helper_in(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '>' || shell->input[j] == '|')
		{
			shell->error->e = i;
			return (1);
		}
	}
	if (j < 0)
		return (0);
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if (j < 0)
		return (0);
	if ((shell->input[j] == '>') || (shell->input[j] == '<' && (j + 1) != i))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}

int	helper_out(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|')
		{
			shell->error->e = i;
			return (1);
		}
	}
	if (j < 0)
		return (0);
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if (j < 0)
		return (0);
	if ((shell->input[j] == '<') || (shell->input[j] == '>' && (j + 1) != i))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}

int	helper_pipe(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|'
			|| shell->input[j] == '>')
		{
			shell->error->e = i;
			return (1);
		}
	}
	if (j < 0)
		return (0);
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if (j < 0)
		return (0);
	if ((shell->input[j] == '<') || (shell->input[j] == '|'
			|| shell->input[j] == '>') || (j == -1))
	{
		shell->error->e = j;
		return (1);
	}
	return (0);
}

int	helper_app_here(t_minishell *shell, int i, int j)
{
	if (i == 2)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|'
			|| shell->input[j] == '>')
		{
			shell->is_here_app = 1;
			shell->error->e = i;
			return (1);
		}
	}
	if (j < 0)
		return (0);
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if (j < 0)
		return (0);
	if ((shell->input[j] == '<') || shell->input[j] == '>')
	{
		shell->is_here_app = 1;
		shell->error->e = j;
		return (1);
	}
	return (0);
}
