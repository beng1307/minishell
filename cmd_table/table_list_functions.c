#include "../minishell.h"

t_cmd_table	*table_lstnew(t_cmd *new_cmd)
{
	t_cmd_table	*new_node;

	new_node = malloc(sizeof(t_cmd_table));
	if (!new_node)
		return (NULL);
	new_node->cmd = new_cmd;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_cmd_table	*table_lstlast(t_cmd_table *lst)
{
	t_cmd_table	*lastlst;

	if (!lst)
		return (NULL);
	lastlst = lst;
	while (lastlst->next != NULL)
		lastlst = lastlst->next;
	return (lastlst);
}

void	table_lstadd_back(t_cmd_table **lst, t_cmd_table *new)
{
	t_cmd_table	*lastlst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		lastlst = table_lstlast(*lst);
		lastlst->next = new;
		new->prev = lastlst;
	}
	new->next = NULL;
}
