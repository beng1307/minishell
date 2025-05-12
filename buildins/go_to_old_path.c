/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_old_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:50:53 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/18 19:21:44 by bgretic          ###   ########.fr       */
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
			return (free(old_cwd), terminator(), 1);
		env_lstadd_back(&env, ft_lstnew_env(new_owd));
		free(new_owd);
	}
	else
	{
		free_that(&old_pwd_node->path);
		old_pwd_node->path = ft_strjoin("OLDPWD=", old_cwd);
		if (!old_pwd_node->path)
			return (free(old_cwd), terminator(), 1);
	}
	return (0);
}

static int	update_pwd(t_minishell *shell, t_env *env, char	*new_cwd)
{
	char	cwd[PATH_MAX];
	t_env	*pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), shell->exitcode = 1, 1);
	pwd = get_pwd_node(env);
	if (!pwd)
	{
		new_cwd = ft_strjoin("PWD=", cwd);
		if (!new_cwd)
			return (terminator(), 1);
		env_lstadd_back(&env, ft_lstnew_env(new_cwd));
	}
	else
	{
		new_cwd = ft_strdup(&pwd->path[4]);
		if (!new_cwd)
			return (terminator(), 1);
		free_that(&pwd->path);
		pwd->path = ft_strjoin("PWD=", cwd);
		if (!pwd->path)
			return (free_that(&new_cwd), terminator(), 1);
	}
	return (update_old_pwd(env, new_cwd),
		free_that(&new_cwd), ft_putendl_fd(cwd, 1), 0);
}

void	go_to_old_path(t_minishell *shell, t_env *env)
{
	t_env	*old_pwd_node;

	old_pwd_node = get_old_pwd_node(env);
	if (old_pwd_node && chdir(&old_pwd_node->path[7]) == -1)
	{
		shell->exitcode = 1;
		error_wrong_path(&old_pwd_node->path[7]);
		return ;
	}
	update_pwd(shell, env, NULL);
}
