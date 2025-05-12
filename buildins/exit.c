/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:17 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/28 20:07:40 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_message(t_minishell *shell, t_tokens *tokens)
{
	write(2, "exit: ", 6);
	ft_putstr_fd(tokens->token, 2);
	write(2, ": numeric argument required\n", 28);
	shell->exitcode = 2;
	shell->called_from_exit = true;
	terminator();
}

bool	check_long_overflow(long sum, long nbr, long sign)
{
	if (sign == 1 && sum > (LONG_MAX - nbr) / 10)
		return (true);
	else if (sign == -1 && (-sum < (LONG_MIN) + nbr) / 10)
		return (true);
	if (sum == 922337203685477580 && nbr == 9)
		return (true);
	return (false);
}

void	assign_long_atoi(long *sum, long *sign, long *i, bool *overflow)
{
	(*sum) = 0;
	(*sign) = 1;
	(*i) = 0;
	(*overflow) = false;
}

long	ft_atoi_long(const char *str, t_minishell *shell, t_tokens *current)
{
	long	i;
	long	sign;
	long	sum;
	bool	overflow;

	assign_long_atoi(&sum, &sign, &i, &overflow);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		overflow = check_long_overflow(sum, str[i] - '0', sign);
		if (overflow == true)
			return (exit_message(shell, current), 999);
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sign * sum);
}

void	my_exit(t_minishell *shell, t_tokens *tokens)
{
	t_tokens	*current;
	long		exit_number;

	current = tokens;
	if (current->next == NULL || current->next->type != WORD)
		return (set_exit_flag(shell), terminator());
	shell->exitcode = 0;
	current = current->next;
	if (current->next && current->next->type == WORD)
	{
		if (is_string_numeric(current->token) == -1)
			exit_message(shell, current);
		else
			write(2, "exit: too many arguments\n", 25);
		shell->exitcode = 1;
		return ;
	}
	if (is_string_numeric(current->token) == -1)
		return ((void)exit_message(shell, current));
	exit_number = ft_atoi_long(current->token, shell, current);
	shell->exitcode = exit_number;
	shell->called_from_exit = true;
	terminator();
}
