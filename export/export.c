#include "../minishell.h"


char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (0);
}

char *ft_own_trim_equal(char *cpy)
{
	char *string;
	int i;

	i = 0;
	while (cpy[i] != '=' && cpy[i] != '\0')
		i++;
	string = ft_substr(cpy, 0, i);
	if (!string)
		return (NULL);
	ft_free(&cpy);
	return (string);
}

void	export_var(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_tokens	*current;
	t_env		*env_copy;
	size_t		len;
	size_t		sec_len;
	size_t		check;
	char		*copy;

	check = 0;
	current = tokens;
	env_copy = env;
	while(current->next != NULL && current->next->type == WORD)
	{
		current = current->next;
		while(env_copy)
		{
			len = ft_strlen_to(current->token);
			sec_len = ft_strlen_to(current->token);
			if (env_copy->path == NULL && env_copy->expp != NULL)
			{
				copy = ft_strjoin("declare -x ", current->token);
				if (!copy)
				{
					shell->exitcode = 1;
					return ;
				}
				if (ft_mini_strrchr(copy, '=') == 0)
					copy = ft_own_trim_equal(copy);
				if (ft_strcmp(env_copy->expp, copy) == 0)
					check = 1;
				if (ft_strcmp(env_copy->expp, copy) == 0 && ft_mini_strrchr(current->token, '=') == 0)
				{
					env_copy->path = current->token;
					ft_free(&env_copy->expp);
					env_copy->expp = ft_strjoin_expp("declare -x ", current->token);
					if (!env_copy->expp)
					{
						free(copy);
						shell->exitcode = 1;
						return ;
					}
					check = 1;
				}
				free(copy);
			}
			else if (env_copy->path)
			{	
				len = ft_strlen_to(env_copy->path);
				if (len == sec_len && ft_strncmp(env_copy->path, current->token, len) == 0)
					check = 1;
				if ((len == sec_len) && ft_strncmp(env_copy->path, current->token, sec_len) == 0 && ft_mini_strrchr(current->token, '=') == 0)
				{
					env_copy->path = current->token;
					ft_free(&env_copy->expp);
					env_copy->expp = ft_strjoin_expp("declare -x ", current->token);
					if (!env_copy->expp)
					{
						shell->exitcode = 1;
						return ;
					}
					check = 1;
				}
			}
			env_copy = env_copy->next;
		}
		if (check != 1)
			env_lstadd_back(&env, ft_lstnew_spec_env(current->token));
		env_copy = env;
		check = 0;
	}
	shell->exitcode = 0;
}

void	ft_print_expp(t_env *env, t_minishell *shell)
{
	t_env *current;
	int	count;
	char **expp_array;
	int	i;

	count = 0;
	i = 0;
	current = env;
	while (current)
	{
		if (!current->expp)
			current = current->next;
		current = current->next;
		count++;
	}
	expp_array = ft_calloc(count + 1, sizeof(char *));
	if (!expp_array)
	{
		shell->exitcode = 1;
		return ;
	}
	current = env;
	while(i < count)
	{
		if (current->expp == NULL)
			current = current->next;
		expp_array[i] = current->expp;
		current = current->next;
		i++;
	}
	bubble_sort(expp_array, count);
	ft_print_array(expp_array);
	free(expp_array);
}

void	export(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	if (tokens->next == NULL || tokens->next->type != WORD)
	{
		ft_print_expp(env, shell);
		return ;
	}
	export_var(shell, tokens, env);
}
