/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_table_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:24 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/19 16:42:46 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_command(t_tokens **tokens_copy, t_cmd **new_cmd)
{
	t_cmd	*lastlst;
	int		index;

	index = 0;
	cmd_lstadd_back(new_cmd, cmd_lstnew());
	lastlst = cmd_lstlast(*new_cmd);
	allocate_command(&lastlst, *tokens_copy);
	while (*tokens_copy && (*tokens_copy)->type == WORD)
	{
		lastlst->command[index] = ft_strdup((*tokens_copy)->token);
		if (!lastlst->command[index])
			return (terminator());
		remove_quotes(&lastlst->command[index]);
		*tokens_copy = (*tokens_copy)->next;
		index++;
	}
	lastlst->type = COMMAND;
}

static void	create_redir(t_tokens **tokens_copy, t_cmd **new_cmd)
{
	t_cmd	*lastlst;

	cmd_lstadd_back(new_cmd, cmd_lstnew());
	lastlst = cmd_lstlast(*new_cmd);
	if (*tokens_copy && (*tokens_copy)->next)
	{
		lastlst->redir = ft_calloc(3, sizeof(char *));
		if (!lastlst->redir)
			return (terminator());
		lastlst->redir[0] = ft_strdup((*tokens_copy)->token);
		if (!lastlst->redir)
			return (terminator());
		lastlst->type = (*tokens_copy)->type;
		*tokens_copy = (*tokens_copy)->next;
		lastlst->redir[1] = ft_strdup((*tokens_copy)->token);
		if (!lastlst->redir)
			return (terminator());
		*tokens_copy = (*tokens_copy)->next;
	}
	check_heredoc_quotes(&lastlst);
	remove_quotes(&lastlst->redir[1]);
}

static void	get_command_if_statements(t_tokens **tokens_copy, t_cmd **new_cmd)
{
	if ((*tokens_copy)->type == INPUT
		|| (*tokens_copy)->type == OUTPUT
		|| (*tokens_copy)->type == APPEND
		|| (*tokens_copy)->type == HEREDOC)
		create_redir(tokens_copy, new_cmd);
	else if ((*tokens_copy)->type == WORD)
		create_command(tokens_copy, new_cmd);
	else
		*tokens_copy = (*tokens_copy)->next;
}

static t_cmd	*get_command(t_tokens **tokens_copy)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	while (*tokens_copy)
	{
		if ((*tokens_copy)->type == PIPE)
		{
			*tokens_copy = (*tokens_copy)->next;
			break ;
		}
		get_command_if_statements(tokens_copy, &new_cmd);
	}
	if (!new_cmd)
	{
		new_cmd = cmd_lstnew();
		if (!new_cmd)
			terminator();
		new_cmd->type = EMPTY_EXPANSION;
	}
	return (new_cmd);
}

t_cmd_table	*init_cmd_table(t_tokens *tokens)
{
	t_tokens	*tokens_copy;
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	tokens_copy = NULL;
	tokens_copy = tokens;
	while (tokens_copy)
		table_lstadd_back(&cmd_table, table_lstnew(
				get_command(&tokens_copy)));
	return (cmd_table);
}
