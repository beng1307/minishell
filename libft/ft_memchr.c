/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:48:11 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 12:44:58 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	i = 0;
	str = (const char *)s;
	while (i < n)
	{
		if (str[i] == (char)c)
		{
			return ((void *)(str + i));
		}
		i++;
	}
	return (NULL);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	test[] = {'q','w','e','r','t'};
	char	*t = ft_memchr(test, 'r', 5);
	
	char	test2[25] = "Hello@World";
	char	*t2 = ft_memchr(test2, '@', 6);

	if (t == NULL)
	{
		printf("Character not found");
	}
	else
	{
		printf("%c", t[0]);
	}
	printf("\n");
	if (t2 == NULL)
    {
        printf("Character 2 not found");
    }
    else
    {
        printf("%s", t2);
    }
}
*/
