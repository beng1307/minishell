/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:56 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 22:31:09 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_handler(t_minishell *shell, char *arg)
{
	char	*new_path;

	if (shell->exec->path != NULL)
		ft_free(&shell->exec->path);
	new_path = ft_strjoin("./", arg);
	if (!new_path)
	{
		free_all_exec(shell, 1);
		terminator();
	}
	if (access(new_path, X_OK) == 0)
		return (new_path);
	ft_putstr_fd(arg, 2);
	if (access(new_path, F_OK) == 0)
	{
		write(2, ": Permission denied\n", 20);
		set_exit_code(shell, 126);
	}
	else
	{
		write(2, ": No such file or directory\n", 28);
		set_exit_code(shell, 127);
	}
	return (ft_free(&new_path), set_exit_flag(shell),
		free_all_exec(shell, 1), terminator(), NULL);
}

char	*find_path_command(t_minishell *shell, char *arg)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (shell->exec->envp[++i] != NULL)
	{
		if (ft_strncmp(shell->exec->envp[i], "PATH=", 5) == 0)
		{
			while (shell->exec->envp[i][len] != '\0')
				len++;
			shell->exec->path = ft_substr(shell->exec->envp[i], 5, len);
			if (!shell->exec->path)
				return (free_array(&shell->exec->args),
					free_memory_array(shell->exec->envp, i), terminator(),
					NULL);
			break ;
		}
	}
	if (shell->exec->path == NULL || ft_strcmp(shell->exec->path, "") == 0)
		return (path_handler(shell, arg));
	shell->exec->path_split = ft_split(shell->exec->path, ':');
	if (!shell->exec->path_split)
		return (free_all_exec(shell, 1), terminator(), NULL);
	if (!*shell->exec->path_split)
		return (free_array(&shell->exec->path_split),\
			free_all_exec(shell, 1), terminator(), NULL);
	return (create_full_path(shell, arg));
}

char	*ft_strjoin_exec(char const *s1, char const *s2)
{
	char	*news;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2) + 2;
	news = (char *)malloc(i * sizeof(char));
	if (news == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		news[j] = s1[j];
		j++;
	}
	news[j++] = '/';
	while (s2[k] != '\0')
	{
		news[j] = s2[k];
		j++;
		k++;
	}
	news[j] = '\0';
	return (news);
}

char	*create_full_path(t_minishell *shell, char *arg)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (shell->exec->path_split[i] != NULL)
	{
		full_path = ft_strjoin_exec(shell->exec->path_split[i], arg);
		if (!full_path)
			return (free_all_exec(shell, 1), terminator(), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_all_exec(shell, 0), full_path);
		ft_free(&full_path);
		i++;
	}
	shell->exec->to_free_exec = true;
	return (free_all_exec(shell, 0), ft_free(&full_path), NULL);
}

int	check_for_slash(char **command, int index)
{
	int	i;

	i = 0;
	while (command[index][i] != '\0')
	{
		if (command[index][i] == '/')
			return (1);
		i++;
	}
	return (0);
}
