/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:52:14 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/19 16:45:37 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_dollar(char **line, int *index)
{
	char	*first_token_part;
	char	*second_token_part;
	char	*new_token;

	first_token_part = ft_substr(*line, 0, *index);
	if (!first_token_part)
		return (terminator());
	second_token_part = ft_substr(*line, *index + 2, ft_strlen(&(*line)[*index
				+ 2]));
	if (!second_token_part)
		return (free(first_token_part), terminator());
	new_token = sh_strjoin(first_token_part, second_token_part, 0, 0);
	if (!new_token)
		return (free(first_token_part), free(second_token_part), terminator());
	free_that(&first_token_part);
	free_that(&second_token_part);
	free_that(line);
	*line = new_token;
	*index = 0;
}

static void	expand_variables(char **line, t_env *env, int *index)
{
	char	*first_token_part;
	char	*second_token_part;
	char	*token;
	int		var_len;

	var_len = get_var_len(&(*line)[*index + 1]);
	first_token_part = ft_substr(*line, 0, *index);
	if (!first_token_part)
		return (terminator());
	token = ft_substr(*line, *index + 1, var_len);
	if (!token)
		return (free(first_token_part), terminator());
	second_token_part = sh_strjoin(heredoc_get_var_content(env, token),
			&(*line)[*index + var_len + 1], 0, 0);
	if (!second_token_part)
		return (free(first_token_part), free(token), terminator());
	free(token);
	token = sh_strjoin(first_token_part, second_token_part, 0, 0);
	if (!token)
		return (free(first_token_part), free(second_token_part), terminator());
	free_that(line);
	*line = token;
	*index = 0;
	return (free_that(&first_token_part), free_that(&second_token_part));
}

static void	expand_exit_codes(char **line, int shell_exitcode, int *index)
{
	char	*first_token_part;
	char	*second_token_part;
	char	*new_token;
	char	*exit_string;

	first_token_part = ft_substr(*line, 0, *index);
	if (!first_token_part)
		return (terminator());
	exit_string = ft_itoa(shell_exitcode);
	if (!exit_string)
		return (free(exit_string), terminator());
	second_token_part = sh_strjoin(exit_string, &(*line)[*index + 2], 0, 0);
	if (!second_token_part)
		return (free(first_token_part), free(exit_string), terminator());
	new_token = sh_strjoin(first_token_part, second_token_part, 0, 0);
	if (!new_token)
		return (free(exit_string), free(first_token_part),
			free(second_token_part), terminator());
	free_that(&exit_string);
	free_that(&first_token_part);
	free_that(&second_token_part);
	free_that(line);
	*line = new_token;
	*index = 0;
}

static void	expand_tilde(char **line, t_env *env, int *index)
{
	char	*new_token;

	new_token = sh_strjoin(get_home(env), &(*line)[*index + 1], 0, 0);
	if (!new_token)
		return (terminator());
	free_that(line);
	*line = new_token;
	*index = 0;
}

void	expand_line(char **line, t_minishell *shell, t_env *env)
{
	int	index;

	index = 0;
	while ((*line)[index])
	{
		if ((*line)[index] == '$' && (is_quote((*line)[index + 1])
				|| ft_isspace((*line)[index + 1]) || (*line)[index
				+ 1] == '\0'))
			index++;
		else if ((*line)[index] == '$' && (*line)[index + 1] == '$')
			remove_dollar(line, &index);
		else if ((*line)[index] == '$' && (*line)[index + 1] != '?')
			expand_variables(line, env, &index);
		else if ((*line)[index] == '$' && (*line)[index + 1] == '?')
			expand_exit_codes(line, shell->exitcode, &index);
		else if ((*line)[index] == '~')
			expand_tilde(line, env, &index);
		else
			index++;
	}
}
