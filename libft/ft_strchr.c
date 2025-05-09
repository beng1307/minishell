/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:57:39 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 14:36:04 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (0);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	test[25] = "Test string!";
	char	*test2 = ft_strchr(test, '\0');

	if (test2 != 0)
	{
		printf("%s", test2);
	}
	else if (test2 == 0)
	{
		printf("The result is NULL");
	}
}
*/
