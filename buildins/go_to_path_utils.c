/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:50:57 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/29 19:17:09 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_old_pwd_node(t_env *env)
{
	t_env	*old_pwd_node;

	old_pwd_node = env;
	while (old_pwd_node)
	{
		if (old_pwd_node->path
			&& ft_strncmp(old_pwd_node->path, "OLDPWD=", 7) == 0)
			return (old_pwd_node);
		old_pwd_node = old_pwd_node->next;
	}
	return (NULL);
}

t_env	*get_pwd_node(t_env *env)
{
	t_env	*pwd_node;

	pwd_node = env;
	while (pwd_node)
	{
		if (pwd_node->path && ft_strncmp(pwd_node->path, "PWD=", 4) == 0)
			return (pwd_node);
		pwd_node = pwd_node->next;
	}
	return (NULL);
}
