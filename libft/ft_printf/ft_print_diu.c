/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:01:35 by bgretic           #+#    #+#             */
/*   Updated: 2024/05/17 14:37:51 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_numlen(long int num)
{
	long int	digit;
	int			len;

	digit = 0;
	len = 1;
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
	return (len);
}

static size_t	ft_numlen_u(size_t num)
{
	size_t	len;

	len = 0;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	len++;
	return (len);
}

void	ft_putnbr_fd_u(unsigned int nb, int fd)
{
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		ft_putchar_fd(nb + '0', fd);
	}
}

//Prints numbers.
size_t	ft_print_d(int n)
{
	size_t	len;

	len = ft_numlen((long)n);
	ft_putnbr_fd(n, 1);
	return (len);
}

//Prints unsigned numbers.
size_t	ft_print_u(unsigned int n)
{
	size_t	len;

	len = ft_numlen_u((size_t)n);
	ft_putnbr_fd_u(n, 1);
	return (len);
}
