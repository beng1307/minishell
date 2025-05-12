/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:50 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/18 18:53:11 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_lstlast(t_env *lst)
{
	t_env	*lastlst;

	if (!lst)
		return (NULL);
	lastlst = lst;
	while (lastlst->next != NULL)
		lastlst = lastlst->next;
	return (lastlst);
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->path = ft_strdup(content);
	if (!new_node->path)
		return (free(new_node), terminator(), NULL);
	new_node->expp = ft_strjoin_expp("declare -x ", content);
	if (!new_node->expp)
		return (free_that(&new_node->path), free(new_node), terminator(), NULL);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*lastlst;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lastlst = env_lstlast(*lst);
		lastlst->next = new;
		new->prev = lastlst;
	}
	new->next = NULL;
}

void	set_shlvl_env(t_env *env, char *shell_var)
{
	int		shlvl;
	char	*shlvl_str;
	char	dest[PATH_MAX];
	char	*shlvl_final;

	ft_bzero(dest, PATH_MAX);
	ft_strlcpy(dest, "SHLVL=", 7);
	shlvl_str = ft_strchr(shell_var, '=');
	if (shlvl_str[1] == '\0')
		env_lstadd_back(&env, ft_lstnew_env("SHLVL=1"));
	shlvl_str++;
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (ft_free(&shlvl_str), terminator());
	shlvl_final = ft_strjoin(dest, shlvl_str);
	if (!shlvl_final)
		return (ft_free(&shlvl_str), terminator());
	ft_free(&shlvl_str);
	env_lstadd_back(&env, ft_lstnew_env(shlvl_final));
	ft_free(&shlvl_final);
}

t_env	*innit_env(t_minishell *shell, char **envp)
{
	t_env	*env;
	size_t	len_to;
	size_t	i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		len_to = ft_strlen_to(envp[i]);
		if (ft_strncmp("_", envp[i], len_to) == 0)
			env_lstadd_back(&env, ft_lstnew_env_underscore(envp[i]));
		else if (ft_strncmp("SHLVL", envp[i], len_to) == 0)
			set_shlvl_env(env, envp[i]);
		else
			env_lstadd_back(&env, ft_lstnew_env(envp[i]));
		i++;
		shell->env = env;
	}
	return (env);
}
