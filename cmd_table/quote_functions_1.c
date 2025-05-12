/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:40 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:51:41 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_quote(int character)
{
	return (character == '\'' || character == '\"');
}

void	check_heredoc_quotes(t_cmd **lastlst)
{
	if (quote_found((*lastlst)->redir[1]))
		(*lastlst)->del_in_quotes = true;
	else
		(*lastlst)->del_in_quotes = false;
}

bool	is_in_quotes(char current_char)
{
	static bool	in_quotes = false;
	static char	delimeter_quote = '\0';

	if (is_quote(current_char))
	{
		if (in_quotes == false)
		{
			in_quotes = true;
			delimeter_quote = current_char;
		}
		else if (in_quotes == true
			&& delimeter_quote == current_char)
		{
			in_quotes = false;
			delimeter_quote = '\0';
		}
	}
	return (in_quotes);
}

bool	quote_found(char *token)
{
	int	index;

	index = 0;
	while (token[index])
	{
		if (is_quote(token[index]))
			return (true);
		index++;
	}
	return (false);
}

bool	is_delimeter_quote(char current_char)
{
	static bool	is_in_quotes = false;
	static char	delimeter_quote = '\0';

	if (is_quote(current_char))
	{
		if (is_in_quotes == false)
		{
			is_in_quotes = true;
			delimeter_quote = current_char;
			return (true);
		}
		else if (is_in_quotes == true
			&& delimeter_quote == current_char)
		{
			is_in_quotes = false;
			delimeter_quote = '\0';
			return (true);
		}
	}
	return (false);
}
