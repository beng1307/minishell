/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:23:12 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 13:03:54 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if ((unsigned char)str1[i] == '\0' || (unsigned char)str2[i] == '\0')
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		else if ((unsigned char)str1[i] != (unsigned char)str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	return (0);
}

//test
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char *av[])
{
	char	*test = av[1];
	char	*test2 = av[2];
	size_t	test3 = atoi(av[3]);

	if (ac == 4)
	{
		if (ft_strncmp(test, test2, test3) < 0)
    	{
			printf("str2 is higher then str1");
    	}
		else if (ft_strncmp(test, test2, test3) > 0)
    	{
			printf("str1 is higher then str2");
    	}
		else
		{
			printf("They are equal");
		}
	}
}
*/
