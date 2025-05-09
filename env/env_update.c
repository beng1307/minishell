#include "../minishell.h"


char *get_last_word_token(t_tokens *tokens)
{
	t_tokens	*tok_copy;

	tok_copy = tokens;
	while(tok_copy->next)
		tok_copy = tok_copy->next;
	while (tok_copy)
	{
		if (tok_copy->type == WORD)
		{
			return (tok_copy->token);
			break ;
		}
		tok_copy = tok_copy->prev;
	}
	if (!tok_copy->token)
		return (NULL);
	return (tok_copy->token);
}

void create__(t_minishell *shell, const char *token)
{
	int i;
	int	k;

	k = 0;
	i = 0;
	shell->upd_env[k++] = '_';
	shell->upd_env[k++] = '=';
	while (token[i] != '\0')
		shell->upd_env[k++] = token[i++];
	shell->upd_env[k] = '\0';
}

void	update_env(t_minishell *shell, t_tokens *tokens, t_env *env) // highly doubted 
{
	t_env		*current;
	t_tokens	*tok_copy;
	int			sensei;

	current = env;
	tok_copy = tokens;
	while(tok_copy->next)
		tok_copy = tok_copy->next;
	while (tok_copy)
	{
		if (tok_copy->type == WORD && ft_strlen(tok_copy->token) < PATH_MAX)
		{
			create__(shell, tok_copy->token);
			break ;
		}
		tok_copy = tok_copy->prev;
	}
	while (current)
	{
		sensei = ft_strlen_to(current->path);
		if (current->path && strncmp("_", current->path, sensei) == 0 && ft_strcmp(shell->upd_env, "_=usr/bin/env") != 0)
		{
			if (*shell->upd_env)
				current->path = shell->upd_env;
			else
				current->path = NULL;
			break ;
		}
		current = current->next;
	}
}