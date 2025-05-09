/* 
char *copy_cop_copy_join(void *content)
{
	char *copy_cop;
	char *copy;
	char *cop;
	size_t	len;

	len = ft_strlen_to(content);
	copy = ft_strchr(content, '=');
	copy++; //copy = (/home/Desktop)
	cop = ft_strjoin("\"", copy);//cop = ("/home/Desktop)
	copy = ft_strdup(cop); //copy = ("/home/Desktop)
	ft_free(&cop);//cop = (NULL);
	cop = ft_strjoin(copy, "\"");//cop = ("/home/Desktop")
	ft_free(&copy);
	copy = cop;
	ft_free(&cop);
	copy_cop = ft_substr(content, 0, len + 1);//copy_cop = (PWD=);
	cop = copy_cop;//cop = (PWD=);
	ft_free(&copy_cop);//copy_cop = (NULL);
	copy_cop = ft_strjoin(cop, copy);
	printf("%s\n", copy_cop);
	return (copy_cop);
}

char **copy_envp(t_minishell *shell, char **envp)
{
	char	**env_path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env_path = (char **)ft_calloc(i + 1, sizeof(char *));
	if (! env_path)
	{
		ft_printf("allocation error\n");
		shell->exitcode = 1;
		return (NULL);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		env_path[i] = ft_strdup(envp[i]);
		if (! env_path)
		{
			free_mem_c_arr(env_path, i);
			ft_printf("allocation error\n");
			shell->exitcode = 1;
			return (NULL);
		}
		i++;
	}
	return (env_path);
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	pwd(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	char	*pwd_env;
	char	cwd[_PC_PATH_MAX];
	int		i;
	t_env		*current;
	t_tokens	*copy_tok;
	i = 0;

	current = env;
	copy_tok = tokens;
	while (current != NULL)
	{
		if (strncmp(shell->env_path->path[i], "PWD=", 4) == 0)
		{
			if (ft_strlen(shell->env_path->path[i]) == 4)
				break ;
			ft_printf("%s\n", shell->env_path->path[i]);
			return ;
		}	
		i++;
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

void	free_memory_array(char **array, int index)
{
	while (index-- > 0)
		ft_free(&array[index]);
	ft_free(array);
}

char	**declare_env(t_minishell *shell)
{
	char	**x_env;
	int		i;

	i = 0;
	while(shell->env_path->path[i] != NULL)
		i++;
	x_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (! x_env)
	{
		ft_printf("allocation error\n");
		shell->exitcode = 1;
		return (NULL);
	}
	i = 0;
	while(shell->env_path->path[i] != NULL)
	{
		x_env[i] = ft_strjoin("declare -x ", shell->env_path->path[i]);
		if (! x_env[i])
		{
			free_mem_c_arr(x_env, i);
			ft_printf("allocation error\n");
			shell->exitcode = 1;
			return (NULL);
		}
		i++;
	}
	return (x_env);
}

void ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

size_t	argument_count(char *string)
{
	int i;
	size_t count;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		while (string[i] == ' ' || string[i] == '\t')
			i++;
		if (string[i] != ' ' && string[i] != '\t')
			count++;
		while (string[i] != ' ' && string[i] != '\t' && string[i] != '\0' && string[i] != '\n')
			i++;
	}
	return (count);
}

size_t	get_index_arr(char **array)
{
	size_t	index;

	index = 0;
	while(array[index] != NULL)
		index++;
	return (index);
}

/* char	**ft_realloc_arr(char **old_memory, size_t old_size, size_t new_size)
{
	char	**new_memory;
	size_t	size;

	if (new_size == 0)
	{
		free_mem_c_arr(old_memory, old_size);
		return (NULL);
	}
	new_memory = (char **)ft_calloc(new_size, sizeof(char *));
	if (!new_memory)
		return (NULL);
	if (new_size > old_size)
		size = old_size;
	else
		size = new_size;
	if (old_memory)
	{
		ft_memmove(new_memory, old_memory, size * sizeof(char *));
		free_mem_c_arr(old_memory, old_size);
	}
	return (new_memory);
}
 
char	**ft_realloc_exp_path(char **old_memory, size_t old_size, size_t new_size)
{
	char	**new_memory;
	size_t	size;

	if (new_size == 0)
	{
		free_mem_c_arr(old_memory, old_size);
		return (NULL);
	}
	new_memory = (char **)ft_calloc(new_size, sizeof(char *));
	if (!new_memory)
		return (NULL);
	if (new_size > old_size)
		size = old_size;
	else
		size = new_size;
	if (old_memory)
	{
		ft_memmove(new_memory, old_memory, size * sizeof(char *));
		free_mem_c_arr(old_memory, old_size);
	}
	return (new_memory);
}

void	ft_realloc_path(t_minishell *shell, char **old_memory, size_t old_size, size_t new_size)
{
	char	**new_memory;
	size_t	size;

	if (new_size == 0)
	{
		free_mem_c_arr(old_memory, old_size);
		return ;
	}
	new_memory = (char **)ft_calloc(new_size, sizeof(char *));
	if (!new_memory)
		return ;
	if (new_size > old_size)
		size = old_size;
	else
		size = new_size;
	if (old_memory)
	{
		ft_memmove(new_memory, old_memory, size * sizeof(char *));
		free_mem_c_arr(old_memory, old_size);
	}
	shell->env_path->path = new_memory;
}

int	ft_mini_strrchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i != -1)
	{
		if (str[i] == (char)c)
			return (0);
		i--;
	}
	return (1);
}

void	path_updater(t_minishell *shell, size_t new_s)
{
	size_t	idx;
	size_t	i;

	idx = 0;
	i = 0;
	while(i < new_s)
	{	
		if (ft_mini_strrchr(shell->env_path->exp_path[i], '=') == 0)
		{
			shell->env_path->path[idx] = ft_substr(shell->env_path->exp_path[i], 11, (ft_strlen(shell->env_path->exp_path[i])));
			if (!(shell->env_path->path[idx]))
			{
				free_mem_c_arr(shell->env_path->path, idx);
				shell->exitcode = 1;
				return ;
			}
			idx++;
		}
		i++;
	}
}

void	update_path(t_minishell *shell)
{
	size_t	old_s;
	size_t	new_s;
	size_t	takeoff;

	old_s = 0;
	new_s = 0;
	takeoff = 0;
	while(shell->env_path->path[old_s] != NULL)
		old_s++;
	while(shell->env_path->exp_path[new_s] != NULL)
	{
		printf("test upd: %s\n", shell->env_path->exp_path[new_s]);
		if (ft_mini_strrchr(shell->env_path->exp_path[new_s], '=') == 1)
			takeoff++;
		new_s++;
	}
	new_s -= takeoff;
	printf("%zu o, %zu n\n", old_s, new_s);
	if(old_s == new_s)
		return ;
	ft_realloc_path(shell, shell->env_path->path, old_s, new_s);
	if (!(shell->env_path->path))
	{
		shell->exitcode = 1;
		return ;
	}
	path_updater(shell, new_s);
}

void	add_exp_variable(t_minishell *shell, char *command, size_t old_s, size_t new_s)
{
	size_t	k;
	size_t	j;
	char	*new_var;

	k = 0;
	j = 0;
	new_var = NULL;
	printf("command %s\n", command);
	printf("%ld, %ld, olds news\n", old_s, new_s);
	while(command[k] == ' ' || command[k] == '\t')
	{
			j++;
			k++;
	}
	while(command[k] != '\0' && command[k] != '\n' && command[k] != ' ' && command[k] != '\t')
			k++;
	new_var = strncpy(new_var, command, (k -j));
	printf("new_var %s", new_var);
	shell->env_path->exp_path[new_s] = new_var;
	shell->env_path->exp_path[new_s + 1] = NULL;

/* 	while (old_s < new_s)
	{
		while(command[k] == ' ' || command[k] == '\t')
			k++;
		new_var = (char *)ft_calloc((ft_strlen(command) - k) + 1, sizeof(char));
		if (!new_var)
		{
			shell->exitcode = 1;
			return;
		}
		while(command[k] != '\0' && command[k] != '\n' && command[k] != ' ' && command[k] != '\t')
			new_var[j++] = command[k++];
		shell->env_path->exp_path[old_s] = new_var;
		old_s++;
	} 
	ft_print_array(shell->env_path->exp_path);
	old_s += 6;
	//update_path(shell);
}		

char **ft_copy_array(t_minishell *shell, char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		shell->env_path->exp_path[i] = ft_strdup(arr[i]);
		if (! shell->env_path->exp_path)
		{
			free_mem_c_arr(shell->env_path->exp_path, i);
			ft_printf("allocation error\n");
			shell->exitcode = 1;
			return (NULL);
		}
		i++;="x=hello
	}
	return (shell->env_path->exp_path);
}

void	export_variable(t_minishell *shell, char *command)
{
	size_t	i;
	size_t	arr_size;
	char **arr;

	arr = shell->env_path->exp_path;
	i = argument_count(command);
	arr_size = get_index_arr(shell->env_path->exp_path);
	free_mem_c_arr(shell->env_path->exp_path, arr_size);
	//shell->env_path->exp_path = ft_realloc_exp_path(shell->env_path->exp_path, arr_size, (arr_size + i));
	shell->env_path->exp_path = (char **)ft_calloc(arr_size + i, sizeof(char *));
	i = 0;
	while(arr[i] !=  NULL)
	{
		shell->env_path->exp_path[i] = ft_strdup(arr[i]);
		i++;
	}

	//shell->env_path->exp_path = ft_copy_array(shell, copy);
	add_exp_variable(shell, command, arr_size, (arr_size + i));
}

void	export(t_minishell *shell, char *command, t_tokens *tokens, t_env *env) //command expandend variable
{
	int	i; 

	i = 0;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	i += 6;
	if (!shell->env_path->exp_path)
			shell->env_path->exp_path = declare_env(shell);
	if (!shell->env_path->exp_path)
		return ;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	if (command[i] == '\n' || command[i] == '\0')
	{
		ft_print_array(shell->env_path->exp_path);
		return ;
	}
	command += 6;
	if (command[0] != ' ' && command[0] != '\t')
	{
		command -= 6;
		ft_printf("command not found %s\n", command);
		shell->exitcode = 127;
		return ;
	}
	export_variable(shell, command);
} */