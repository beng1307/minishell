/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:53:49 by bgretic           #+#    #+#             */
/*   Updated: 2025/01/02 17:55:03 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// displays prompt on a new line
void	handle_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_heredoc = 1;
		soft_terminator();
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrl_d(t_minishell *shell)
{
	shell->called_from_exit = true;
	terminator();
}

void	signal_handler(void)
{
	g_signal_heredoc = 0;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
