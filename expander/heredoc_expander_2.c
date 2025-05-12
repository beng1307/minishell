/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:52:21 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:52:22 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_get_var_content(t_env *env, char *to_search)
{
	t_env	*env_index;
	int		length;

	if (!*to_search)
		return (to_search);
	length = ft_strlen(to_search);
	env_index = env;
	while (env_index)
	{
		if (ft_strncmp(env_index->path, to_search, length) == 0
			&& env_index->path[length] == '=')
		{
			if (env_index->path[length + 1])
				return (&env_index->path[length + 1]);
		}
		env_index = env_index->next;
	}
	return (NULL);
}

char	*get_home(t_env *env)
{
	t_env	*env_index;
	char	*home;

	env_index = env;
	home = NULL;
	while (env_index)
	{
		if (ft_strncmp(env_index->path, "HOME=", 5) == 0)
		{
			home = ft_strdup(&env_index->path[5]);
			if (!home)
				return (terminator(), NULL);
			break ;
		}
		env_index = env_index->next;
	}
	return (home);
}
