#include "../minishell.h"

bool is_quote(char character)
{
	return (character == '\'' || character == '\"');
}

bool	is_in_quotes(char current_char)
{
	static bool	in_quotes = false;
	static char	delimeter_quote = '\0';

	if (is_quote(current_char))
	{
		if (in_quotes == false)
		{
			in_quotes = true;
			delimeter_quote = current_char;
		}
		else if (in_quotes == true
			&& delimeter_quote == current_char)
		{
			in_quotes = false;
			delimeter_quote = '\0';
		}
	}
	return (in_quotes);
}

static bool	quote_found(char *token)
{
	int	index;

	index = 0;
	while (token[index])
	{
		if (is_quote(token[index]))
			return (true);
		index++;
	}
	return (false);
}

static bool	is_delimeter_quote(char current_char)
{
	static bool	is_in_quotes = false;
	static char	delimeter_quote = '\0';

	if (is_quote(current_char))
	{
		if (is_in_quotes == false)
		{
			is_in_quotes = true;
			delimeter_quote = current_char;
			return (true);
		}
		else if (is_in_quotes == true 
			&& delimeter_quote == current_char)
		{
			is_in_quotes = false;
			delimeter_quote = '\0';
			return (true);
		}
	}
	return (false);
}

static int	quote_free_token_length(char *token)
{
	int	length;

	length = 0;
	while (*token)
	{
		if (!is_delimeter_quote(*token))
			length++;
		token++;
	}
	return (length);
}

static void	remove_quotes(char **token)
{
	char	*quote_free_token;
	int		indexI;
	int		indexII;

	indexI = 0;
	indexII = 0;
	quote_free_token = ft_calloc(quote_free_token_length(*token) + 1, sizeof(char));
	while ((*token)[indexI])
	{
		if (is_delimeter_quote((*token)[indexI]))
			indexI++;
		else
			quote_free_token[indexII++] = (*token)[indexI++]; 
	}
	free_that(token);
	*token = quote_free_token;
}

//Protect it
static void	allocate_command(t_cmd **lastlst, t_tokens *tokens_copy)
{
	int	size_count;

	size_count = 0;
	while (tokens_copy && tokens_copy->type == WORD)
	{
		size_count++;
		tokens_copy = tokens_copy->next;
	}
	(*lastlst)->command = ft_calloc(size_count + 1, sizeof(char *));
}

//Protect it
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
		// if (!lastlst->args[index])
		// 	return (NULL);
		remove_quotes(&lastlst->command[index]);
		*tokens_copy = (*tokens_copy)->next;
		index++;
	}
	lastlst->type = COMMAND;
}

static void	check_heredoc_quotes(t_cmd **lastlst)
{
	if (quote_found((*lastlst)->redir[1]))
		(*lastlst)->del_in_quotes = true;
	else
		(*lastlst)->del_in_quotes = false;
}

//Protect it
static void	create_redir(t_tokens **tokens_copy, t_cmd **new_cmd)
{
	t_cmd	*lastlst;

	cmd_lstadd_back(new_cmd, cmd_lstnew());
	lastlst = cmd_lstlast(*new_cmd);
	if (*tokens_copy && (*tokens_copy)->next)
	{
		lastlst->redir = ft_calloc(3, sizeof(char *));
		// if (!lasrlst->redir)
		//	implement check
		lastlst->redir[0] = ft_strdup((*tokens_copy)->token);
		// if (!lastlst->redir)
		//	implement check
		lastlst->type = (*tokens_copy)->type;
		*tokens_copy = (*tokens_copy)->next;
		lastlst->redir[1] = ft_strdup((*tokens_copy)->token);
		// if (!lastlst->redir)
		//	implement check
		*tokens_copy = (*tokens_copy)->next;
	}
	//else error
	check_heredoc_quotes(&lastlst);
	remove_quotes(&lastlst->redir[1]);
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
		if ((*tokens_copy)->type == INPUT
			|| (*tokens_copy)->type == OUTPUT
			|| (*tokens_copy)->type == APPEND
			|| (*tokens_copy)->type == HEREDOC)
			create_redir(tokens_copy, &new_cmd);
		else if ((*tokens_copy)->type == WORD)
			create_command(tokens_copy, &new_cmd);
	}
	return (new_cmd);
}

t_cmd_table	*init_cmd_table(t_tokens *tokens)
{
	t_tokens	*tokens_copy;
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	tokens_copy = tokens;
	while (tokens_copy)
		table_lstadd_back(&cmd_table, table_lstnew(
			get_command(&tokens_copy)));
	return (cmd_table);
}
