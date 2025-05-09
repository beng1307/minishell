/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:48 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 12:44:41 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long int num)
{
	long int	digit;
	int			len;

	digit = 0;
	len = 0;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num >= 10)
	{
		digit = num / 10;
		num = digit;
		len++;
	}
	len += 2;
	return (len);
}

static char	ft_strrev(char *str)
{
	char	temp[12];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i] == '-')
	{
		i++;
		j++;
	}
	while (str[i] != '\0')
	{
		temp[i] = str[i];
		i++;
	}
	while (i > 0 && str[j] != '\0')
	{
		str[j] = temp[i - 1];
		i--;
		j++;
	}
	return (*str);
}

char	*ft_itoa(int n)
{
	long int	num;
	char		*str;
	int			len;
	int			i;

	num = (long)n;
	len = ft_numlen(num);
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (num < 0)
	{
		str[i++] = '-';
		num = -num;
	}
	while (i < len - 1)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	*test;
	int		num;

	num = -214748364;
	test = ft_itoa(num);
	printf("%s", test);
}
*/
