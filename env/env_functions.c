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
	new_node->path = content;
	new_node->expp = ft_strjoin_expp("declare -x ", content);
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

t_env *innit_env(char **envp)
{
	t_env *env;
	size_t	len_to;
	size_t	i;

	i = 0;
	env = NULL;
	while(envp[i] != NULL)
	{
		len_to = ft_strlen_to(envp[i]);
		if (strncmp("_", envp[i], len_to) == 0)
			env_lstadd_back(&env, ft_lstnew_env_underscore(envp[i]));
		else
			env_lstadd_back(&env, ft_lstnew_env(envp[i]));
		i++;
	}
	return (env);
}

void	env_lstclear(t_env **lst, void (*del)(char **))
{
	t_env	*to_clear;

	if (lst && del)
	{
		to_clear = *lst;
		while (to_clear != NULL)
		{
			to_clear = to_clear->next;
			del(&(*lst)->expp);
			del(&(*lst)->path);
			free(*lst);
			*lst = to_clear;
		}
	}
}

/* void	ft_lstdelone(t_env **lst, void (*del)(char **))
{
	if (lst && del)
	{
		del(&(*lst)->path);
		del(&(*lst)->expp);
		free(*lst);
	}
} */

/* void	env_unset(t_env **lst)
{
	(*lst)->prev->next = (*lst)->next;
	if (lst)
	{
		ft_free(&(*lst)->path);
		ft_free(&(*lst)->expp);
		free(*lst);
	}
} */
