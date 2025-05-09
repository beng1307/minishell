#include "../minishell.h"

t_tokens	*shell_lstnew(char *content)
{
	t_tokens	*new_node;

	new_node = malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->token = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_tokens	*shell_lstlast(t_tokens *lst)
{
	t_tokens	*lastlst;

	if (!lst)
		return (NULL);
	lastlst = lst;
	while (lastlst->next != NULL)
		lastlst = lastlst->next;
	return (lastlst);
}

void	shell_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*lastlst;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lastlst = shell_lstlast(*lst);
		lastlst->next = new;
		new->prev = lastlst;
	}
	new->next = NULL;
}

void	shell_lstclear(t_tokens **lst, void (*del)(char **))
{
	t_tokens	*to_clear;

	if (lst && del)
	{
		to_clear = *lst;
		while (to_clear != NULL)
		{
			to_clear = to_clear->next;
			del(&(*lst)->token);
			free(*lst);
			*lst = to_clear;
		}
	}
}
