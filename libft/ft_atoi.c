/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:17:09 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/29 11:37:05 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	minusnbr;
	int	nbr;

	minusnbr = 0;
	nbr = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minusnbr += 1;
		nptr++;
	}
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	if (minusnbr == 1)
		return (-nbr);
	return (nbr);
}

//test
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int	test;
	
		test = ft_atoi(av[1]);
		printf("%d", test);
	}
	return (0);
}
*/
