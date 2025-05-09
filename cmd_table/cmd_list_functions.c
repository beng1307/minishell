#include "../minishell.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	// new_node->command = NULL;
	new_node->command = NULL;
	new_node->redir = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	t_cmd	*lastlst;

	if (!lst)
		return (NULL);
	lastlst = lst;
	while (lastlst->next != NULL)
		lastlst = lastlst->next;
	return (lastlst);
}

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*lastlst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		lastlst = cmd_lstlast(*lst);
		lastlst->next = new;
		new->prev = lastlst;
	}
	new->next = NULL;
}
