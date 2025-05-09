/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:45:15 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/26 12:52:55 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
		ft_putnbr_fd(nb, fd);
	}
	else if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		ft_putchar_fd(nb + '0', fd);
	}
}

//test
/*
int	main(void)
{
	int	num1 = 3;
	int num2 = 13;
	int num3 = 2147483647;
	int num4 = -1;
	int num5 = -214783648;

	ft_putnbr_fd(num1, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(num2, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(num3, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(num4, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(num5, 1);
}
*/
