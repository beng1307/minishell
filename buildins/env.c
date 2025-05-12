/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:06 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/18 15:16:47 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env_underscore(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->path = ft_strdup(content);
	if (!new_node->path)
	{
		free(new_node);
		terminator();
	}
	new_node->expp = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	create_undersc_env(t_env *env)
{
	t_env	*current;
	size_t	len_to;
	char	*env_path;
	size_t	check;

	env_path = "_=usr/bin/env";
	current = env;
	check = 0;
	while (current)
	{
		len_to = ft_strlen_to(current->path);
		if (ft_strncmp("_", current->path, len_to) == 0)
		{
			free_that(&current->path);
			current->path = ft_strdup(env_path);
			if (!current->path)
				return (terminator());
			check = 1;
			break ;
		}
		current = current->next;
	}
	if (check == 0)
		env_lstadd_back(&env, ft_lstnew_env_underscore(env_path));
}

void	env_buildin(t_minishell *shell, t_env *env)
{
	t_env	*current;

	current = env;
	shell->exitcode = 0;
	create_undersc_env(env);
	while (current)
	{
		if (current->path)
			ft_printf("%s\n", current->path);
		current = current->next;
	}
}
