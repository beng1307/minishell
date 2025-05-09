/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:16:31 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 13:04:41 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_c_in_set(const char *str, const char *c)
{
	while (*c)
	{
		if (*str == *c)
			return (1);
		c++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (is_c_in_set((char *)s1, set) == 1)
		s1++;
	len = ft_strlen((char *)s1);
	while (*s1 && is_c_in_set(&s1[len - 1], set) == 1)
		len--;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, (char *)s1, len);
	return (str);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t"));
}
*/
