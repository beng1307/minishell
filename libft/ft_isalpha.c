/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:24:56 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/09 19:26:04 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int argument)
{
	if ((argument >= 'A' && argument <= 'Z'))
	{
		return (1);
	}
	else if ((argument >= 'a' && argument <= 'z'))
	{
		return (2);
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

	if (isalpha(c) == 0)
	{
		printf("%c is not an alphabet.", c);
	}
	else
	{
		printf("%c is an alphabet.", c);
	}
}
*/
