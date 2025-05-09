/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:26:00 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 12:45:21 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((int)str1[i] - (int)str2[i]);
		}
		i++;
	}
	return (0);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	test[25] = "test";
	char	test2[25] = "test";

	ft_memcmp(test, test2, 20);
	if (ft_memcmp(test, test2, 20) < 0)
	{
		printf("s2 is higher then s1");
	}
	else if (ft_memcmp(test, test2, 20) > 0)
	{
		printf("s1 is higher then s2");
	}
	else if (ft_memcmp(test, test2, 20) == 0)
	{
		printf("They are equal");
	}
}
*/
