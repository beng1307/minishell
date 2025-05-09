/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:20 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/09 19:25:40 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int argument)
{
	if ((argument >= 'a' && argument <= 'z')
		|| (argument >= 'A' && argument <= 'Z')
		|| (argument >= '0' && argument <= '9'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	c;

	printf("Enter a character: ");
	scanf("%c", &c);

	if (isalnum(c) == 0)
	{
		printf("%c is not an alphanumeric character.", c);
	}
	else
	{
		printf("%c is an alphanumeric character.", c);
	}
}
*/
