/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:54:43 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/09 17:56:18 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*counter;
	int		count;

	counter = lst;
	count = 0;
	while (counter != NULL)
	{
		count++;
		counter = counter->next;
	}
	return (count);
}
