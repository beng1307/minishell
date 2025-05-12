/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:57 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/18 15:13:17 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstclear(t_env **lst, void (*del)(char **))
{
	t_env	*to_clear;

	if (lst && del)
	{
		to_clear = *lst;
		while (to_clear != NULL)
		{
			to_clear = to_clear->next;
			del(&(*lst)->expp);
			del(&(*lst)->path);
			free(*lst);
			*lst = to_clear;
		}
	}
}

void	create__(t_minishell *shell, const char *token) // allocate for _
{
	int	i;
	int	k;

	k = ft_strlen(token);
	i = 0;
	if (shell->upd_env)
		free(shell->upd_env);
	shell->upd_env = (char *)ft_calloc(k + 3, sizeof(char));
	if (!shell->upd_env)
		terminator();
	k = 0;
	shell->upd_env[k++] = '_';
	shell->upd_env[k++] = '=';
	while (token[i] != '\0')
		shell->upd_env[k++] = token[i++];
	shell->upd_env[k] = '\0';
}

void	create_env_var(t_minishell *shell, t_tokens *tokens)
{
	t_tokens	*tok_copy;

	tok_copy = tokens;
	while (tok_copy && tok_copy->next)
		tok_copy = tok_copy->next;
	while (tok_copy)
	{
		if (tok_copy->type == WORD && ft_strlen(tok_copy->token) < PATH_MAX)
		{
			create__(shell, tok_copy->token);
			break ;
		}
		tok_copy = tok_copy->prev;
	}
}

void	update_env_helper(t_minishell *shell, t_env *env, int check)
{
	if (check == 0)
		env_lstadd_back(&env, ft_lstnew_env_underscore(shell->upd_env));
	shell->env = env;
	free_that(&shell->upd_env);
}

void	update_env(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_env		*current;
	int			len_to;
	int			check;

	check = 0;
	current = env;
	create_env_var(shell, tokens);
	while (current)
	{
		len_to = ft_strlen_to(current->path);
		if ((current->path) && ft_strncmp("_", current->path, len_to) == 0)
		{
			if (shell->upd_env)
			{
				ft_free(&current->path);
				current->path = ft_strdup(shell->upd_env);
				if (!current->path)
					return (terminator());
			}
			check = 1;
			break ;
		}
		current = current->next;
	}
	update_env_helper(shell, env, check);
}
