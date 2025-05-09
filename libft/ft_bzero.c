/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:17:14 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/12 12:49:24 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*terminate;

	i = 0;
	terminate = (char *)s;
	while (i < n)
	{
		*terminate = '\0';
		terminate++;
		i++;
	}
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	test[16] = "ITestMyFunction";
	int		i;

	i = 0;	
	printf("%s\n", test);
	ft_bzero(test, 7);
	while (i < 16)
	{
		printf("%c", test[i]);
		i++;
	}
}
*/
