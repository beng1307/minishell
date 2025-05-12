/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:41:23 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/18 15:14:28 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_var_helper(t_minishell *shell, t_tokens **current)
{
	if ((*current)->next->type == WORD)
		(*current) = (*current)->next;
	else
	{
		while ((*current)->next && (*current)->next->type != WORD)
		{
			if ((*current)->next->type == BREAK_NODE)
			{
				shell->exp_valid = false;
				return (1);
			}
			(*current) = (*current)->next;
		}
	}
	return (0);
}

void	export_var_helper_2(t_tokens **current, t_env *env_copy,
	size_t *check, char *copy)
{
	copy = ft_strjoin("declare -x ", (*current)->token);
	if (!copy)
		terminator();
	if (ft_mini_strrchr(copy, '=') == 0)
	{
		copy = ft_own_trim_equal(copy);
		if (!copy)
			terminator();
	}
	michael_checkson(env_copy, check, copy);
	if (ft_strcmp(env_copy->expp, copy) == 0
		&& ft_mini_strrchr((*current)->token, '=') == 0)
	{
		free_that(&env_copy->path);
		env_copy->path = ft_strdup((*current)->token);
		if (!env_copy->path)
			return (free(copy), terminator());
		ft_free(&env_copy->expp);
		env_copy->expp = ft_strjoin_expp("declare -x ",
				(*current)->token);
		if (!env_copy->expp)
			return (free(copy), terminator());
		(*check) = 1;
	}
	free(copy);
}

void	export_var_helper_3(t_tokens **current, t_env *env_copy, size_t *check)
{
	size_t	len;
	size_t	sec_len;

	sec_len = ft_strlen_to((*current)->token);
	len = ft_strlen_to(env_copy->path);
	if (len == sec_len
		&& ft_strncmp(env_copy->path, (*current)->token, len) == 0)
		(*check) = 1;
	if ((len == sec_len) && ft_strncmp(env_copy->path,
			(*current)->token, sec_len) == 0
		&& ft_mini_strrchr((*current)->token, '=') == 0)
	{
		ft_free(&env_copy->path);
		env_copy->path = ft_strdup((*current)->token);
		if (!env_copy->path)
			terminator();
		ft_free(&env_copy->expp);
		env_copy->expp = ft_strjoin_expp("declare -x ",
				(*current)->token);
		if (!env_copy->expp)
			terminator();
		(*check) = 1;
	}
}

void	export_main_loop(t_minishell *shell,
	t_env *env_copy, t_tokens *current, size_t *check)
{
	while (env_copy && shell->exp_valid == true)
	{
		if (env_copy->path == NULL && env_copy->expp != NULL)
			export_var_helper_2(&current, env_copy, check, NULL);
		else if ((env_copy->path))
			export_var_helper_3(&current, env_copy, check);
		env_copy = env_copy->next;
	}
}

void	export_var(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_tokens	*current;
	t_env		*env_copy;
	size_t		check;

	check = 0;
	current = tokens;
	env_copy = env;
	while (current->next != NULL)
	{
		if (export_var_helper(shell, &current) == 1)
			return ;
		if (shell->exp_valid == true)
			if (full_export_check(current->token, shell) == 1)
				check = 1;
		export_main_loop(shell, env_copy, current, &check);
		if (check != 1)
			env_lstadd_back(&env, ft_lstnew_spec_env(current->token));
		env_copy = env;
		check = 0;
		shell->exp_valid = true;
	}
}
