/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:45:15 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 14:06:54 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_to_allocate(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	mem;

	mem = 0;
	s_len = (size_t)ft_strlen((char *)s);
	if (start > s_len)
		mem = 0;
	else if (start + len > s_len)
		mem = s_len - start;
	else if (start + len <= s_len)
		mem = len;
	return (mem);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		size;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	size = size_to_allocate(s, start, len);
	str = ft_calloc(size + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (size == 0)
		return (str);
	while (s[start + i] != '\0' && i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

//test
/*
#include <stdio.h>

int	main(void)
{					
	char	*test = "01234";
	char	*test2;

	printf("%u\n", ft_strlen(test));
	test2 = ft_substr(test, 10, 10);
	if (test2 == NULL)
		printf("NULL");
	else
		printf("%s\n", test2);
	free(test2);
}
*/
