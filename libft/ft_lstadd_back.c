/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:52:52 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/09 17:55:49 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastlst;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lastlst = ft_lstlast(*lst);
		lastlst->next = new;
	}
	new->next = NULL;
}
