/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:56 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 17:26:55 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	generate_heredoc_name(t_minishell *shell)
{
	static int	nbr = 0;
	char		*string;

	nbr++;
	string = ft_itoa(nbr);
	shell->exec->heredoc = ft_strjoin("/tmp/heredog", string);
	if (!shell->exec->heredoc)
		return (free(string), terminator(), 1);
	if (access(shell->exec->heredoc, F_OK) == 0)
	{
		if (unlink(shell->exec->heredoc) == -1)
		{
			return (free_that(&shell->exec->heredoc), \
			free(string), generate_heredoc_name(shell));
		}
	}
	free(string);
	return (0);
}

void	print_heredoc_message(t_minishell *shell, char *del)
{
	write(2, "warning: here-document at line ", 31);
	ft_putnbr_fd(shell->shell_loop, 2);
	write(2, " delimited by end-of-file (wanted `", 35);
	ft_putstr_fd(del, 2);
	write(2, "')\n", 3);
}

int	open_heredoc(t_minishell *shell)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	shell->exec->infile = open(shell->exec->heredoc, O_CREAT | O_RDWR | O_TRUNC,
			0644);
	if (shell->exec->infile == -1)
	{
		shell->exitcode = 1;
		return (perror(shell->exec->heredoc), 1);
	}
	return (0);
}

void	wait_out_of_gio(void)
{
	while (wait(NULL) != -1)
		;
}
