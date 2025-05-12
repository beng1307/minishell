/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:13 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/22 20:31:47 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_char_to_new_token(char **new_token, t_tokens *token_cpy,
		int new_token_length, int *index)
{
	*new_token = ft_realloc(*new_token, new_token_length + 1);
	if (!*new_token)
		return (terminator());
	(*new_token)[new_token_length] = token_cpy->token[*index];
	(*new_token)[new_token_length + 1] = '\0';
	(*index)++;
}

bool	cmd_is_echo_singleton(t_tokens *token_cpy)
{
	static bool	cmd_is_echo = false;

	if (token_cpy->type == INPUT || token_cpy->type == OUTPUT
		|| token_cpy->type == APPEND || token_cpy->type == HEREDOC
		|| token_cpy->type == PIPE)
		cmd_is_echo = false;
	if (ft_cmp(token_cpy->token, "echo") || ft_cmp(token_cpy->token,
			"/bin/echo"))
		cmd_is_echo = true;
	return (cmd_is_echo);
}

void	init_expand_vars(t_tokens **token_copy, t_tokens **tokens,
bool *empty_expansion, char **new_token)
{
	(*token_copy) = (*tokens);
	(*empty_expansion) = false;
	(*new_token) = NULL;
}

void	free_and_check(char **curr_new_token,
			char *new_token, t_tokens **token_cpy)
{
	free_that(curr_new_token);
	if (!new_token)
		return (free_that(&(*token_cpy)->token), terminator());
}
