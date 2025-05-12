/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:48 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/28 18:45:18 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_heredoc = 1;
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	heredoc_signal_handler(void)
{
	signal(SIGINT, heredoc_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	write_in_heredoc(t_minishell *shell, char *line)
{
	write(shell->exec->infile, line, ft_strlen(line));
	write(shell->exec->infile, "\n", 1);
}

int	create_heredoc_line(char **line, t_minishell *shell, char *del)
{
	*line = readline("> ");
	if (!line || !*line)
	{
		shell->shell_loop++;
		print_heredoc_message(shell, del);
		return (1);
	}
	return (0);
}

int	create_heredoc(t_cmd *cmd, t_minishell *shell, t_env *env, char *del)
{
	char	*line;

	line = NULL;
	if (open_heredoc(shell) == 1)
		return (1);
	while (shell->exec->master_splinter_is_king)
	{
		heredoc_signal_handler();
		if (create_heredoc_line(&line, shell, del) == 1)
			break ;
		if (g_signal_heredoc == 1)
			return (close_heredoc(shell), free_that(&line), 1);
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		if (cmd->del_in_quotes == false)
			expand_line(&line, shell, env);
		write_in_heredoc(shell, line);
		free(line);
		shell->shell_loop++;
	}
	return (close(shell->exec->infile), 0);
}
