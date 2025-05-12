/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:53:17 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/22 00:33:34 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection_operator(int character)
{
	if (character == '|' || character == '<' || character == '>')
		return (true);
	return (false);
}

static char	*get_word(char *shell_input)
{
	char	*word;
	int		token_length;

	token_length = 0;
	while ((shell_input[token_length]
			&& is_in_quotes(shell_input[token_length]))
		|| (shell_input[token_length]
			&& !is_redirection_operator(shell_input[token_length])
			&& (shell_input[token_length] != ' '
				&& shell_input[token_length] != '\t')))
		token_length++;
	word = ft_calloc(token_length + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, shell_input, token_length + 1);
	return (word);
}

int	tokenize_word(t_tokens **tokens, char *shell_input, int *index)
{
	char	*token;

	token = get_word(&shell_input[*index]);
	if (!token)
		return (shell_lstclear(tokens, free_that), terminator(), -1);
	shell_lstadd_back(tokens, shell_lstnew(token));
	*index += ft_strlen(token) - 1;
	return (0);
}

int	tokenize_redirection_operator(
		t_tokens **tokens, char *shell_input, int index)
{
	if (shell_input[index] == '|')
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup("|")));
	else if (shell_input[index] == '<' && shell_input[index + 1] != '<')
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup("<")));
	else if (shell_input[index] == '<' && shell_input[index + 1] == '<')
	{
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup("<<")));
		index++;
	}
	else if (shell_input[index] == '>' && shell_input[index + 1] != '>')
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup(">")));
	else if (shell_input[index] == '>' && shell_input[index + 1] == '>')
	{
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup(">>")));
		index++;
	}
	return (index);
}
