/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:17 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:51:18 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
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

void	cmd_lstclear(t_cmd **lst, void (del)(char ***))
{
	t_cmd	*to_clear;

	if (lst && del)
	{
		to_clear = *lst;
		while (to_clear != NULL)
		{
			to_clear = to_clear->next;
			del(&(*lst)->command);
			del(&(*lst)->redir);
			free(*lst);
			*lst = to_clear;
		}
	}
}
