/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_terminator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:31 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/20 19:58:50 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	soft_terminator(void)
{
	t_minishell	*shell;

	shell = get_shell_data();
	shell->blank = false;
	shell->fu_dog_goat = true;
	if (shell->unequal_quotes == true)
		write(2, "Unequal amount of quotes\n", 25);
	shell->unequal_quotes = false;
	free_content(shell);
}

static void	free_table(t_cmd_table **table)
{
	table_lstclear(table, cmd_lstclear);
}

static void	free_tokens(t_tokens **tokens)
{
	shell_lstclear(tokens, free_that);
}

void	free_content(t_minishell *shell)
{
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	if (shell->exec->prev_fd != -1)
	{
		close(shell->exec->prev_fd);
		shell->exec->prev_fd = -1;
	}
	if (shell->tokens)
		free_tokens(&shell->tokens);
	if (shell->table)
		free_table(&shell->table);
}
