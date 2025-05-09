/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:49:13 by bgretic           #+#    #+#             */
/*   Updated: 2024/05/26 13:35:09 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*to;
	const char	*from;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = 0;
	to = (char *)dest;
	from = (const char *)src;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dest);
}

//test
/*
#include <stdio.h>
int	main(void)
{
	char	test[6] = "Hello";
	char	test2[6];

	ft_memcpy(test2, test, 6);
	printf("%s", test2);
}
*/
