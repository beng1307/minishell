/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:52:26 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/22 19:27:42 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_lstadd_between(t_tokens **lst, t_tokens *new)
{
	t_tokens	*next_token;

	next_token = (*lst)->next;
	(*lst)->next = new;
	new->prev = *lst;
	new->next = next_token;
	if (next_token)
		next_token->prev = new;
}

void	split_token(t_tokens **tokens_copy, int index1, int index2)
{
	shell_lstadd_between(tokens_copy,
		shell_lstnew(ft_strdup(&(*tokens_copy)->token[index2])));
	(*tokens_copy)->token = ft_realloc((*tokens_copy)->token, index1);
	if (!(*tokens_copy)->token)
		return (terminator());
}

void	process_token(t_tokens **tokens_copy, bool *first_spaces)
{
	int	index1;
	int	index2;

	index1 = 0;
	while ((*tokens_copy)->token[index1])
	{
		if (!is_in_quotes((*tokens_copy)->token[index1])
			&& (*tokens_copy)->token[index1] == ' ')
		{
			index2 = index1;
			while ((*tokens_copy)->token[index2] == ' ' && !(*first_spaces))
				index2++;
			if ((*tokens_copy)->token[index2])
			{
				split_token(tokens_copy, index1, index2);
				break ;
			}
		}
		*first_spaces = false;
		index1++;
	}
}

void	word_splitting(t_tokens **tokens)
{
	t_tokens	*tokens_copy;
	bool		first_spaces;

	tokens_copy = *tokens;
	first_spaces = true;
	while (tokens_copy)
	{
		process_token(&tokens_copy, &first_spaces);
		tokens_copy = tokens_copy->next;
	}
}
