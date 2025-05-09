#include "../minishell.h"

static t_env	*get_pwd_node(t_env *env)
{
	t_env	*pwd_node;

	pwd_node = env;
	while (pwd_node)
	{
		if (ft_strncmp(pwd_node->path, "PWD=", 4) == 0)
			return (pwd_node);
		pwd_node = pwd_node->next;
	}
	return (NULL);
}

static int	update_pwd(t_minishell *shell, t_env *env)
{
	char	cwd[PATH_MAX];
	t_env	*pwd_node;

	pwd_node = get_pwd_node(env);
	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), shell->exitcode = 1, 1);
	if (!pwd_node)
		env_lstadd_back(&env, ft_lstnew_env(ft_strjoin("PWD=", cwd)));
	else
	{
		free(pwd_node->path);
		pwd_node->path = ft_strjoin("PWD=", cwd);
		// if (!pwd_node->path)
		// 	implement exit_function
	}
	return (0);
}

static void	go_to_path(t_minishell *shell, t_env *env, char *path)
{
	if (chdir(path) == -1)
	{
		shell->exitcode = 1;
		perror("chdir");
		return ;
	}
	update_pwd(shell, env);
}

static void	go_to_home_directory(t_minishell *shell, t_env *env)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		shell->exitcode = 1;
		perror("getenv");
		return ;
	}
	if (chdir(path) == -1)
	{
		shell->exitcode = 1;
		perror("chdir");
	}
	update_pwd(shell, env);
}

void	cd(t_minishell *shell, t_env *env, char *path)
{
	if (!path)
		go_to_home_directory(shell, env);
	else
		go_to_path(shell, env, path);
}
