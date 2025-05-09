/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:35:35 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/29 11:58:03 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;

	i = 0;
	dest_length = ft_strlen((const char *)dest);
	src_length = ft_strlen(src);
	if (dest_length >= size)
	{
		return (size + src_length);
	}
	while (src[i] != '\0' && i < (size - dest_length) - 1)
	{
		dest[dest_length + i] = src[i];
		i++;
	}
	dest[dest_length + i] = '\0';
	return (dest_length + src_length);
}

//test
/*
int	main(void)
{
	char	test[25] = "Hello";
	char	test2[25] = "Friene";

	printf("%zu\t", ft_strlcat(NULL,test2,0));
	printf("%zu\t", strlcat(NULL,test2,0));
	printf("%s", test);
}
*/
