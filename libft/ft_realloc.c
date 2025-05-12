/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:58:04 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/21 23:19:39 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	free_mem(void **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	*ft_realloc(void *old_memory, size_t new_size)
{
	void	*new_memory;

	new_memory = (void *)ft_calloc(new_size + 1, 1);
	if (!new_memory)
		return (free_mem(&old_memory), NULL);
	if (old_memory)
	{
		ft_memcpy(new_memory, old_memory, new_size);
		free_mem(&old_memory);
	}
	return (new_memory);
}

// void	*ft_realloc(void *old_memory, size_t new_size)
// {
// 	void	*new_memory;

// 	if (new_size == 0)
// 	{
// 		free(old_memory);
// 		return (NULL);
// 	}
// 	new_memory = (void *)ft_calloc(new_size + 1, 1);
// 	if (!new_memory)
// 		return (free(old_memory), NULL);
// 	if (old_memory)
// 	{
// 		ft_memmove(new_memory, old_memory, new_size);
// 		free (old_memory);
// 	}
// 	return (new_memory);
// }
