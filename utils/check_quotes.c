/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:53:32 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/21 20:10:19 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_quotes_helper(t_minishell *shell, int index)
{
	while (shell->input[index])
	{
		if (shell->input[index] == '\'')
		{
			index++;
			while (shell->input[index] != '\'')
			{
				if (!shell->input[index])
					return (false);
				index++;
			}
		}
		else if (shell->input[index] == '\"')
		{
			index++;
			while (shell->input[index] != '\"')
			{
				if (!shell->input[index])
					return (false);
				index++;
			}
		}
		index++;
	}
	return (true);
}

bool	check_quotes(t_minishell *shell)
{
	int	index;

	index = 0;
	return (check_quotes_helper(shell, index));
}
