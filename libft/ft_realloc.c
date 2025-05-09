/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:58:04 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/11 16:58:05 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old_memory, size_t old_size, size_t new_size)
{
	void	*new_memory;
	size_t	size;

	if (new_size == 0)
	{
		free(old_memory);
		return (NULL);
	}
	new_memory = (void *)ft_calloc(new_size, 1);
	if (!new_memory)
		return (free(old_memory), NULL);
	if (new_size > old_size)
		size = old_size;
	else
		size = new_size;
	if (old_memory)
	{
		ft_memmove(new_memory, old_memory, size);
		free (old_memory);
	}
	return (new_memory);
}
