/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xXp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:02:00 by bgretic           #+#    #+#             */
/*   Updated: 2024/05/17 20:53:10 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//Counts the length of the hexadecimal.
static size_t	ft_hexlen(unsigned long int hex)
{
	size_t	len;

	len = 0;
	if (hex == 0)
		len++;
	while (hex > 0)
	{
		len++;
		hex /= 16;
	}
	return (len);
}

//Prints the hexadecimal in lower characters.
size_t	ft_print_x(unsigned int x)
{
	size_t	len;

	len = ft_hexlen(x);
	if (x <= 9)
		ft_putchar_fd(x + '0', 1);
	else if (x >= 16)
	{
		ft_print_x(x / 16);
		ft_print_x(x % 16);
	}
	else
		ft_putchar_fd((x - 10) + 'a', 1);
	return (len);
}

//Prints the hexadecimal in upper characters.
size_t	ft_print_upper_x(unsigned int X)
{
	size_t	len;

	len = ft_hexlen(X);
	if (X <= 9)
		ft_putchar_fd(X + '0', 1);
	else if (X >= 16)
	{
		ft_print_upper_x(X / 16);
		ft_print_upper_x(X % 16);
	}
	else
		ft_putchar_fd((X - 10) + 'A', 1);
	return (len);
}

void	ft_print_address(unsigned long int address)
{
	if (address <= 9)
		ft_putchar_fd(address + '0', 1);
	else if (address >= 16)
	{
		ft_print_address(address / 16);
		ft_print_address(address % 16);
	}
	else
		ft_putchar_fd((address - 10) + 'a', 1);
}

//Prints the address.
size_t	ft_print_p(void *p)
{
	size_t				len;
	unsigned long int	address;

	if (!p)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	address = (unsigned long int)p;
	len = ft_hexlen(address);
	write(1, "0x", 2);
	ft_print_address(address);
	return (len + 2);
}
