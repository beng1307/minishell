#include "../minishell.h"

int	check_for_slash(char **command)
{
	int	i;

	i = 0;
	while (command[0][i] != '\0')
	{
		if (command[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**copy_envp(t_env *env, t_minishell *shell)
{
	t_env *current;
	char **envp;
	int count;

	current = env;
	envp = NULL;
	count = 0;
	while (current)
	{
		current = current->next;
		while (current && current->path == NULL)
			current = current->next;
		count++;
	}
	current = env;
	envp = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!envp)
	{
		shell->exitcode = 1;
		return (NULL);
	}
	count = 0;
	while (current)
	{
		while (current && current->path == NULL)
			current = current->next;
		if (!current)
			break ;
		envp[count] = strdup(current->path);
		if (!envp[count])
		{
			free_memory_array(envp, count);
			shell->exitcode = 1;
			return (NULL);
		}
		current = current->next;
		count++;
	}
	return (envp);
}
