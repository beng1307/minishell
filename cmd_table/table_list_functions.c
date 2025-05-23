/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:51 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:51:52 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	table_lstclear(
		t_cmd_table **lst, void (del)(t_cmd **, void (del)(char ***)))
{
	t_cmd_table	*to_clear;

	if (lst && del)
	{
		to_clear = *lst;
		while (to_clear != NULL)
		{
			to_clear = to_clear->next;
			del(&(*lst)->cmd, free_str_arr);
			free(*lst);
			*lst = to_clear;
		}
	}
}
