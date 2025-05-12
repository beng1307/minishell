/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:13 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:38:14 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit_exit(int arg)
{
	if ((arg >= '0' && arg <= '9') || (arg == '+') || (arg == '-')
		|| (arg == ' ') || (arg == '\t'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	is_string_mult_arit(char *string)
{
	int	i;
	int	pluscount;
	int	minuscount;

	i = 0;
	pluscount = 0;
	minuscount = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '+')
			pluscount++;
		if (string[i] == '-')
			minuscount++;
		i++;
	}
	if (pluscount > 1 || minuscount > 1 || (pluscount + minuscount > 1))
		return (-1);
	return (0);
}

int	is_string_just_arit(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] != '+' && string[i] != '-')
			return (0);
		i++;
	}
	return (-1);
}

int	is_string_with_white(char *string)
{
	int	i;

	i = 0;
	while (string[i] == ' ' || string[i] == '\t')
		i++;
	while (string[i] != ' ' && string[i] != '\t' && string[i] != '\0')
		i++;
	while (string[i] == ' ' || string[i] == '\t')
		i++;
	if (string[i] != '\0')
		return (-1);
	return (0);
}

int	is_string_numeric(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_isdigit_exit(string[i]) == 0)
			return (-1);
		i++;
	}
	if (is_string_just_arit(string) == -1)
		return (-1);
	if (is_string_mult_arit(string) == -1)
		return (-1);
	if (is_string_with_white(string) == -1)
		return (-1);
	return (0);
}
