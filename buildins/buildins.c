#include "../minishell.h"

t_env	*ft_lstnew_env_underscore(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->path = content;
	new_node->expp = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void create_undersc_env(t_env *env)
{
	t_env		*current;
	size_t		len_to;
	char		*env_path = "_=usr/bin/env";
	size_t		check;

	current = env;
	check = 0;
	while (current)
	{
		len_to = ft_strlen_to(current->path);
		if (strncmp("_", current->path, len_to) == 0)
		{
			current->path = env_path;
			check = 1;
		}
		current = current->next;
	}
	if (check == 0)
		env_lstadd_back(&env, ft_lstnew_env_underscore(env_path));
}

void	env_buildin(t_env *env)
{
	t_env *current;

	current = env;
	create_undersc_env(env);
	while (current)
	{
		if (current->path)
			ft_printf("%s\n", current->path);
		current = current->next;
	}
}

void	echo(t_minishell *shell, t_tokens *tokens)
{
	t_tokens *current;

	current = tokens;
	shell->exitcode = 0;
	if (current->next != NULL) // echo loop over tokens !
		current = current->next;
	else 
	{
		write(1, "\n", 1);
		return ;
	}
	if (strncmp(current->token, "-n", 2) == 0)
	{
		while (current->next != NULL && current->next->type == WORD)
		{
			current = current->next;
			ft_printf("%s ", current->token);
		}
		rl_on_new_line();
		return ;
	}
	else
	{
		while (current != NULL && current->type == WORD)
		{
			ft_printf("%s ", current->token);
			current = current->next;
		}
	}
	write(1, "\n", 1);
}
/* 	else if (strncmp(current->token, "$?", 2) == 0)
	{
		ft_printf("%d ", shell->exitcode);
		while (current->next != NULL && current->next->type == WORD)
		{
			current = current->next;
			ft_printf("%s ", current->next->token);
		}
	} */

void	pwd(t_minishell *shell, t_env *env)
{
	char	*pwd_env;
	char	cwd[_PC_PATH_MAX];
	t_env		*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strncmp(current->path, "PWD=", 4) == 0)
		{
			if (ft_strlen(current->path) == 4)
				break ;
			ft_printf("%s\n", current->path);
			return ;
		}	
		current = current->next;
	}
	pwd_env = getenv("PWD");
	if (pwd_env)
		ft_printf("%s\n", pwd_env);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s\n", cwd);
		else
		{
			perror("getcwd() error");
			shell->exitcode = 1;
		}
	}
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

char	*ft_strrchr_until(char *str, int c) //write a strchr until =
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
	{
		str[i] = '\0';
		return *(&str);
	}
	return (0);
}

void	env_unset(t_env **lst)
{
	t_env	*temp;

	temp = *lst;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	if (temp->path)
		temp->path = NULL;
	if (temp->expp)
		ft_free(&(temp)->expp);
	free(temp);
}

void	unset(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_tokens	*current;
	t_env		*copy_env;
	char		*copy;

	current = tokens;
	copy_env = env;
	if (current->next == NULL || current->next->type != WORD)
		return ;
	while(current->next && current->next->type == WORD)
	{
		current = current->next;
		while(copy_env && copy_env->path != NULL)
		{
			copy = ft_strdup(copy_env->path);
			copy = ft_strrchr_until(copy, '=');
			if (ft_strcmp(copy, current->token) == 0)
			{	
				env_unset(&copy_env);
				ft_free(&copy);
				break ;
			}
			ft_free(&copy);
			copy_env = copy_env->next;
		}
		copy_env = env;
	}
	shell->exitcode = 0;
}
