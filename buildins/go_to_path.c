/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:01 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/18 19:20:45 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	update_old_pwd(t_env *env, char *old_cwd)
{
	t_env	*old_pwd_node;
	char	*new_owd;

	old_pwd_node = get_old_pwd_node(env);
	if (!old_pwd_node)
	{
		new_owd = ft_strjoin("OLDPWD=", old_cwd);
		if (!new_owd)
			return (terminator(), 1);
		env_lstadd_back(&env, ft_lstnew_env(new_owd));
		free(new_owd);
	}
	else
	{
		free_that(&old_pwd_node->path);
		old_pwd_node->path = ft_strjoin("OLDPWD=", old_cwd);
		if (!old_pwd_node->path)
			return (terminator(), 1);
	}
	return (0);
}

static int	update_pwd(t_minishell *shell, t_env *env, char *old_cwd)
{
	char	cwd[PATH_MAX];
	char	*new_cwd;
	t_env	*pwd_node;

	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), shell->exitcode = 1, 1);
	pwd_node = get_pwd_node(env);
	if (!pwd_node)
	{
		new_cwd = ft_strjoin("PWD=", cwd);
		if (!new_cwd)
			return (terminator(), 1);
		env_lstadd_back(&env, ft_lstnew_env(new_cwd));
	}
	else
	{
		free_that(&pwd_node->path);
		pwd_node->path = ft_strjoin("PWD=", cwd);
		if (!pwd_node->path)
			return (terminator(), 1);
	}
	update_old_pwd(env, old_cwd);
	return (0);
}

void	go_to_path(t_minishell *shell, t_env *env, char *path, char *old_cwd)
{
	if (chdir(path) == -1)
	{
		shell->exitcode = 1;
		error_wrong_path(path);
		return ;
	}
	update_pwd(shell, env, old_cwd);
}

void	go_to_home_directory(t_minishell *shell, t_env *env, char *old_cwd)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		shell->exitcode = 1;
		error_wrong_path(path);
		return ;
	}
	if (chdir(path) == -1)
	{
		shell->exitcode = 1;
		perror("chdir");
	}
	update_pwd(shell, env, old_cwd);
}
