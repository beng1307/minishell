/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:37:26 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 21:25:21 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_echo_flag(const char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		str += 2;
		while (*str)
		{
			if (*str != 'n')
				return (false);
			str++;
		}
		return (true);
	}
	else
		return (false);
}

int	is_there_another_word(t_tokens *current)
{
	t_tokens	*copy;

	copy = current;
	while (copy->next && copy->next->type != BREAK_NODE)
	{
		copy = copy->next;
		if (copy->type == WORD)
			return (1);
	}
	return (0);
}

void	write_token(t_tokens *current)
{
	ft_printf("%s", current->token);
	if (current->next != NULL && is_there_another_word(current) == 1)
		ft_printf(" ");
}

int	echo_sigpipe_handler(t_minishell *shell)
{
	if (shell->exec->redir_flag == true)
	{
		signal(SIGPIPE, SIG_IGN);
		return (1);
	}
	return (0);
}

void	echo(t_minishell *shell, t_tokens *tokens)
{
	t_tokens	*current;
	bool		no_flag;

	no_flag = true;
	current = tokens;
	shell->exitcode = 0;
	if (echo_sigpipe_handler(shell) == 1)
		return ;
	if (current->next != NULL)
		current = current->next;
	else
		return (write(1, "\n", 1), (void) NULL);
	if (current && is_echo_flag(current->token))
		no_flag = false;
	while (current && is_echo_flag(current->token))
		current = current->next;
	while (current && current->type != BREAK_NODE)
	{
		if (current->type == WORD)
			write_token(current);
		current = current->next;
	}
	if (no_flag)
		write(1, "\n", 1);
}
