#include "../minishell.h"

static bool	is_in_singlequotes(char current_char, int index)
{
	static bool	in_squotes = false;
	static bool	in_dquotes = false;

	if (index == 0)
	{
		in_squotes = false;
		in_dquotes = false;
	}
	if (current_char == '\"' && !in_squotes)
	{
		if (in_dquotes == false)
			in_dquotes = true;
		else
			in_dquotes = false;
	}
	else if (current_char == '\'' && !in_dquotes)
	{
		if (in_squotes == false)
			in_squotes = true;
		else
			in_squotes = false;
	}
	return (in_squotes);
}

static int	get_var_len(char *token)
{
	int	length;

	length = 0;
	while (token[length]
		&& token[length] != '/' && token[length] != '$'
		&& token[length] != '\"' && token[length] != '\''
		&& token[length] != ' ')
		length++;
	return (length);
}

static char	*get_var_content(t_env *env, char *to_search)
{
	t_env	*env_index;
	int		length;

	if (!*to_search)
		return (to_search);
	length = ft_strlen(to_search);
	env_index = env;
	while (env_index)
	{
		if (ft_strncmp(env_index->path, to_search, length) == 0
			&& env_index->path[length] == '=')
		{
			if (env_index->path[length + 1])
				return (&env_index->path[length + 1]);
		}
		env_index = env_index->next;
	}
	return (NULL);
}

static void expand_variable(t_tokens **token_cpy, t_env *env, int *index)
{
	char	*first_token_part;
	char	*second_token_part;
	char	*new_token;
	int		var_len;

	var_len = get_var_len(&(*token_cpy)->token[*index + 1]);
	first_token_part = ft_substr((*token_cpy)->token, 0, *index);
	// if (!first_token_part)
	// 	implement check
	second_token_part = sh_strjoin(
		get_var_content(env, ft_substr((*token_cpy)->token, *index + 1, var_len)),
		&(*token_cpy)->token[*index + var_len + 1]);
	// if (!second_token_part)
	// 	implement check
	new_token = sh_strjoin(first_token_part, second_token_part);
	// if (!new_token)
	// 	implement check;
	free_that(&first_token_part);
	free_that(&second_token_part);
	free_that(&(*token_cpy)->token);
	(*token_cpy)->token = new_token;
	*index = 0;
}

///////////////////////////////////////////////////////////////////////////////

static char	*get_home(t_env *env)
{
	t_env	*env_index;
	char	*home;

	env_index = env;
	home = NULL;
	while (env_index)
	{
		if (ft_strncmp(env_index->path, "HOME=", 5) == 0)
		{
			home = ft_strdup(&env_index->path[5]);
			if (!home)
				return (NULL);
			break ;
		}
		env_index = env_index->next;
	}
	return (home);
}

static void expand_tilde(t_tokens **token_cpy, t_env *env, int *index)
{
	char	*new_token;

	new_token = sh_strjoin(get_home(env), &(*token_cpy)->token[*index + 1]);
	// if (!new_token)
	// 	implement check
	free_that(&(*token_cpy)->token);
	(*token_cpy)->token = new_token;
	*index = 0;
}

///////////////////////////////////////////////////////////////////////////////

static void	expand_exit_code(t_tokens **token_cpy, int shell_exitcode, int *index)
{
	char	*first_token_part;
	char	*second_token_part;
	char	*new_token;

	first_token_part = ft_substr((*token_cpy)->token, 0, *index);
	// if (!first_token_part)
	// 	implement check
	second_token_part = sh_strjoin(ft_itoa(shell_exitcode), &(*token_cpy)->token[*index + 2]);
	// if (!second_part)
		// implement check
	new_token = sh_strjoin(first_token_part, second_token_part);
	// if (!new_token)
		// implement check
	free_that(&first_token_part);
	free_that(&second_token_part);
	free_that(&(*token_cpy)->token);
	(*token_cpy)->token = new_token;
	*index = 0;
}

///////////////////////////////////////////////////////////////////////////////

void	expand(t_minishell *shell, t_tokens **tokens, t_env *env)
{
	t_tokens	*token_cpy;
	int			index;

	token_cpy = *tokens;
	while (token_cpy)
	{
		index = 0;
		while (token_cpy->token && token_cpy->token[index])
		{
			if (!is_in_singlequotes(token_cpy->token[index], index))
			{
				if (token_cpy->token[index] == '$'
					&& token_cpy->token[index + 1] != '?'
					&& token_cpy->token[index + 1] != '$')
				{
					expand_variable(&token_cpy, env, &index);
					index = 0;
				}
				else if (token_cpy->token[index] == '$'
					&& token_cpy->token[index + 1] == '?')
				{
					expand_exit_code(&token_cpy, shell->exitcode, &index);
					index = 0;
				}
				else if (token_cpy->token[index] == '~')
				{
					expand_tilde(&token_cpy, env, &index);
					index = 0;
				}
				else
					index++;
			}
			else
				index++;
		}
		token_cpy = token_cpy->next;
	}
}

/*
TO_DO:

There is still a bug onm this case: $$$HOME/minishell$U$

The wrong output:

"/home/bgretic/minishellER=bgretic"

Check strncmp on get_var_content!
*/
