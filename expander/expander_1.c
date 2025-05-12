/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:52:03 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/22 17:48:55 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	if_statements_expander_2(t_tokens *token_cpy, t_env *env,
		char **new_token, int *index)
{
	t_minishell	*shell;
	bool		empty_expansion;

	shell = get_shell_data();
	empty_expansion = false;
	if (token_cpy->token[*index] == '$' && token_cpy->token[*index + 1] == '$')
		(*index)++;
	else if (token_cpy->token[*index] == '$'
		&& token_cpy->token[*index + 1] != '?')
		empty_expansion = expand_variable(new_token, &token_cpy, env, index);
	else if (token_cpy->token[*index] == '$'
		&& token_cpy->token[*index + 1] == '?')
		expand_exit_code(new_token, shell->exitcode, index);
	else
		copy_char_to_new_token(new_token, token_cpy,
			ft_strlen(*new_token), index);
	return (empty_expansion);
}

static bool	if_statements_expander(t_tokens *token_cpy, t_env *env,
		char **new_token, int *index)
{
	bool	cmd_is_echo;
	bool	empty_expansion;

	cmd_is_echo = cmd_is_echo_singleton(token_cpy);
	empty_expansion = false;
	if (token_cpy->token[*index] == '$'
		&& (is_quote(token_cpy->token[*index + 1])
			|| ft_isspace(token_cpy->token[*index + 1])
			|| token_cpy->token[*index + 1] == '\0'
			|| token_cpy->token[*index + 1] == '/') && cmd_is_echo == true)
		copy_char_to_new_token(new_token, token_cpy,
			ft_strlen(*new_token), index);
	else if (!is_in_singlequotes(token_cpy->token[*index], *index))
		empty_expansion = if_statements_expander_2(
				token_cpy, env, new_token, index);
	else
		copy_char_to_new_token(new_token, token_cpy,
			ft_strlen(*new_token), index);
	return (empty_expansion);
}

static void	assign_new_token(t_tokens **token_cpy,
	char *new_token, bool empty_expansion)
{
	free_that(&(*token_cpy)->token);
	(*token_cpy)->token = new_token;
	if (empty_expansion && !*new_token)
		(*token_cpy)->type = EMPTY_EXPANSION;
}

static void	expand_assign_variables(int *index,
		char **new_token, bool *is_prev_heredoc)
{
	*index = 0;
	*new_token = NULL;
	*is_prev_heredoc = false;
}

void	expand(t_tokens **tokens, t_env *env, t_minishell *shell)
{
	t_tokens	*token_cpy;
	char		*new_token;
	bool		is_prev_heredoc;
	bool		empty_expansion;
	int			index;

	init_expand_vars(&(token_cpy), tokens, &(empty_expansion), &(new_token));
	while (token_cpy)
	{
		expand_assign_variables(&index, &new_token, &is_prev_heredoc);
		while (token_cpy->token && token_cpy->token[index])
		{
			if (token_cpy->prev && token_cpy->prev->type == HEREDOC)
			{
				is_prev_heredoc = true;
				break ;
			}
			empty_expansion = if_statements_expander(
					token_cpy, env, &new_token, &index);
		}
		if (!is_prev_heredoc)
			assign_new_token(&token_cpy, new_token, empty_expansion);
		token_cpy = token_cpy->next;
	}
	shell->new_token = new_token;
}
