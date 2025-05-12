/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:37 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/30 16:34:03 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr_until(char *str, int c) // write a strchr until =
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
	{
		str[i] = '\0';
		return (*(&str));
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
		ft_free(&(temp)->path);
	if (temp->expp)
		ft_free(&(temp)->expp);
	free(temp);
}

void	unset_path_var(t_env *copy_env,
	t_tokens *current, char *copy, t_env *env)
{
	while (copy_env)
	{
		if (copy_env->path)
		{
			copy = ft_strdup(copy_env->path);
			if (!copy)
				return (terminator());
			copy = ft_strrchr_until(copy, '=');
		}
		else
		{
			copy = ft_substr(copy_env->expp, 11, ft_strlen(copy_env->expp));
			if (!copy)
				return (terminator());
		}
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

void	unset_variable(t_minishell *shell,
t_tokens *current, t_env *copy_env, t_env *env)
{
	char	*copy;

	copy = NULL;
	if (current->next == NULL || is_there_another_word(current) == 0)
		return ;
	while (current->next && is_there_another_word(current) == 1)
	{
		current = current->next;
		unset_path_var(copy_env, current, copy, env);
	}
	shell->exitcode = 0;
}

void	unset(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_tokens	*current;
	t_env		*copy_env;

	current = tokens;
	copy_env = env;
	shell->exitcode = 0;
	unset_variable(shell, current, copy_env, env);
}
