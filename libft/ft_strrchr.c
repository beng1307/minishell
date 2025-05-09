/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:58:07 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/22 17:10:17 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i != -1)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i--;
	}
	return (0);
}

//test
/*
#include <stdio.h>

int main(int ac, char **av)
{
	char	*test;
	char	test2;
	char	*test3;

	test = av[1];
    test2 = *av[2];
    test3 = ft_strrchr(test, test2);
	if (ac == 3)
	{
		if (test3 != 0)
		{
			printf("%s", test3);
    	}
    	else if (test3 == 0)
		{
        	printf("The result is NULL");
    	}
	}
}
*/
