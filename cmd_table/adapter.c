/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:11 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/09 21:40:49 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	if_statements_if_else(t_tokens **tokens, t_cmd *cmd,
		t_tokens *lastlst, int *index)
{
	if (cmd->redir)
	{
		while (cmd->redir && cmd->redir[*index])
		{
			shell_lstadd_back(tokens,
				shell_lstnew(ft_strdup(cmd->redir[(*index)++])));
			lastlst = shell_lstlast(*tokens);
			lastlst->type = cmd->type;
		}
	}
	else
	{
		shell_lstadd_back(tokens, shell_lstnew(ft_strdup("")));
		lastlst = shell_lstlast(*tokens);
		lastlst->type = EMPTY_EXPANSION;
	}
}

static void	adapt_cmd_if_statements(t_tokens **tokens, t_cmd *cmd,
		t_tokens *lastlst, int *index)
{
	if (cmd->type == COMMAND)
	{
		while (cmd->command[*index])
		{
			shell_lstadd_back(tokens,
				shell_lstnew(ft_strdup(cmd->command[(*index)++])));
			lastlst = shell_lstlast(*tokens);
			lastlst->type = WORD;
		}
	}
	else
		if_statements_if_else(tokens, cmd, lastlst, index);
}

static void	adapt_cmd(t_tokens **tokens, t_cmd *cmd)
{
	t_tokens	*lastlst;
	int			index;

	lastlst = NULL;
	index = 0;
	adapt_cmd_if_statements(tokens, cmd, lastlst, &index);
}

static void	create_break_node(t_tokens **tokens)
{
	t_tokens	*lastlst;

	shell_lstadd_back(tokens, shell_lstnew(ft_strdup("\0")));
	lastlst = shell_lstlast(*tokens);
	lastlst->type = BREAK_NODE;
}

void	adapter(t_tokens **tokens, t_cmd_table **table)
{
	t_cmd_table	*table_copy;
	t_cmd		*cmd_copy;

	table_copy = *table;
	shell_lstclear(tokens, free_that);
	while (table_copy)
	{
		cmd_copy = table_copy->cmd;
		while (cmd_copy)
		{
			adapt_cmd(tokens, cmd_copy);
			cmd_copy = cmd_copy->next;
		}
		if (table_copy->next)
			create_break_node(tokens);
		table_copy = table_copy->next;
	}
}
