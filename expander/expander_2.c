/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:52:09 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/22 20:31:27 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_var_len(char *token)
{
	int	length;

	length = 0;
	while (token[length] && token[length] != '/' && token[length] != '$'
		&& token[length] != '\"' && token[length] != '\''
		&& token[length] != ' ' && token[length] != '?')
		length++;
	return (length);
}

char	*get_var_content(t_env *env, char *to_search, bool *empty_expansion)
{
	t_env	*env_index;
	int		length;

	if (!*to_search)
		return (to_search);
	length = ft_strlen(to_search);
	env_index = env;
	while (env_index)
	{
		if (env_index->path
			&& ft_strncmp(env_index->path, to_search, length) == 0
			&& env_index->path[length] == '=')
		{
			if (env_index->path[length + 1])
				return (&env_index->path[length + 1]);
		}
		env_index = env_index->next;
	}
	*empty_expansion = true;
	return (NULL);
}

static void	init_expand_variable_variables(char **new_token, char **var_name,
			char **var_content, bool *empty_expansion)
{
	*new_token = NULL;
	*var_name = NULL;
	*var_content = NULL;
	*empty_expansion = false;
}

bool	expand_variable(char **curr_new_token, t_tokens **token_cpy, t_env *env,
		int *index)
{
	char	*new_token;
	char	*var_name;
	char	*var_content;
	int		var_len;
	bool	empty_expansion;

	init_expand_variable_variables(&new_token, &var_name,
		&var_content, &empty_expansion);
	var_len = get_var_len(&(*token_cpy)->token[*index + 1]);
	var_name = ft_substr((*token_cpy)->token, *index + 1, var_len);
	if (!var_name)
		return (free_that(&(*token_cpy)->token),
			free_that(curr_new_token), terminator(), empty_expansion);
	var_content = ft_strdup(get_var_content(env, var_name, &empty_expansion));
	if (!var_content && !empty_expansion)
		return (free_that(&(*token_cpy)->token),
			free(var_name), free_that(curr_new_token),
			terminator(), empty_expansion);
	free(var_name);
	new_token = sh_strjoin(*curr_new_token, var_content, 0, 0);
	free(var_content);
	free_and_check(curr_new_token, new_token, token_cpy);
	*curr_new_token = new_token;
	*index += var_len + 1;
	return (empty_expansion);
}

void	expand_exit_code(char **curr_new_token, int shell_exitcode, int *index)
{
	char	*new_token;
	char	*exit_string;

	exit_string = ft_itoa(shell_exitcode);
	if (!exit_string)
		return (terminator());
	new_token = sh_strjoin(*curr_new_token, exit_string, 0, 0);
	free_that(curr_new_token);
	free(exit_string);
	if (!new_token)
		return (terminator());
	*curr_new_token = new_token;
	*index += 2;
}
