/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:44 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:51:45 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_free_token_length(char *token)
{
	int	length;

	length = 0;
	while (*token)
	{
		if (!is_delimeter_quote(*token))
			length++;
		token++;
	}
	return (length);
}

void	remove_quotes(char **token)
{
	char	*quote_free_token;
	int		index1;
	int		index2;

	index1 = 0;
	index2 = 0;
	quote_free_token = ft_calloc(
			quote_free_token_length(*token) + 1, sizeof(char));
	if (!quote_free_token)
		return (terminator());
	while ((*token)[index1])
	{
		if (is_delimeter_quote((*token)[index1]))
			index1++;
		else
			quote_free_token[index2++] = (*token)[index1++];
	}
	free_that(token);
	*token = quote_free_token;
}

bool	is_in_singlequotes(char current_char, int index)
{
	static bool	in_squotes = false;
	static bool	in_dquotes = false;

	if (index == 0)
	{
		in_squotes = false;
		in_dquotes = false;
	}
	if (current_char == '\"' && !in_squotes)
	{
		if (in_dquotes == false)
			in_dquotes = true;
		else
			in_dquotes = false;
	}
	else if (current_char == '\'' && !in_dquotes)
	{
		if (in_squotes == false)
			in_squotes = true;
		else
			in_squotes = false;
	}
	return (in_squotes);
}
