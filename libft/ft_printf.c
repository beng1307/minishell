/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:29:55 by bgretic           #+#    #+#             */
/*   Updated: 2024/05/17 20:16:21 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Handles the edgecase when there is a % sign without spezifier.
static size_t	ft_error_handle_single_pers(const char *str)
{
	const char	*formats;
	size_t		multiple_pers_check;

	formats = "cspdiuxX%";
	multiple_pers_check = 0;
	while (*str)
	{
		if (*str == '%')
		{
			if (*str == '%' && ft_strchr(formats, *(str + 1)) == 0)
				return (1);
			multiple_pers_check = 1;
		}
		if (multiple_pers_check == 0)
			str++;
		else
			str += 2;
		multiple_pers_check = 0;
	}
	return (0);
}

//Prints the needed format.
static void	ft_print_it(const char *str, size_t *to_return, va_list list)
{
	if (*(str + 1) == 'c')
		*to_return += ft_print_c(va_arg(list, int));
	else if (*(str + 1) == '%')
		*to_return += write(1, "%", 1);
	else if (*(str + 1) == 's')
		*to_return += ft_print_s(va_arg(list, char *));
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		*to_return += ft_print_d(va_arg(list, int));
	else if (*(str + 1) == 'u')
		*to_return += ft_print_u(va_arg(list, unsigned int));
	else if (*(str + 1) == 'x')
		*to_return += ft_print_x(va_arg(list, unsigned long int));
	else if (*(str + 1) == 'X')
		*to_return += ft_print_upper_x(va_arg(list, unsigned long int));
	else if (*(str + 1) == 'p')
		*to_return += ft_print_p(va_arg(list, void *));
}

//Does what printf does.
int	ft_printf(const char *str, ...)
{
	va_list	list;
	size_t	to_return;
	size_t	check;

	if (!str)
		return (-1);
	to_return = 0;
	va_start(list, str);
	if (ft_error_handle_single_pers(str) == 1)
		return (-1);
	while (*str)
	{
		check = to_return;
		if (*str == '%')
			ft_print_it(str++, &to_return, list);
		else
			to_return += write(1, &*str, 1);
		if (check == to_return && (*(str) != 's'))
			return (-1);
		str++;
	}
	va_end(list);
	return ((int)to_return);
}
