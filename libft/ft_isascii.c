/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:10:26 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/09 19:23:09 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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

int main(void)
{
	int	test1 = '!';
	int test2 = 127;
	int test3 = 128;

	if (ft_isascii(test1) == 1)
	{
		printf("%d is an ASCII character\n", test1);
	}
	else
	{
		printf("%d is not an ASCII character\n", test1);
	}
	if (ft_isascii(test2) == 1)
    {
        printf("%d is an ASCII character\n", test2);
    }
    else
    {
        printf("%d is not an ASCII character\n", test2);
    }
	if (ft_isascii(test3) == 1)
    {
        printf("%d is an ASCII character\n", test3);
    }
    else
    {
        printf("%d is not an ASCII character\n", test3);
    }
}
*/
