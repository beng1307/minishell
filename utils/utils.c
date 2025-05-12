/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:41:09 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/28 20:01:51 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_last_word_token(t_tokens *tokens)
{
	t_tokens	*tok_copy;

	tok_copy = tokens;
	while (tok_copy->next)
		tok_copy = tok_copy->next;
	while (tok_copy)
	{
		if (tok_copy->type == WORD)
		{
			return (tok_copy->token);
			break ;
		}
		tok_copy = tok_copy->prev;
	}
	if (!tok_copy->token)
		return (NULL);
	return (tok_copy->token);
}

void	michael_checkson(t_env *env_copy, size_t *check, char *copy)
{
	if (ft_strcmp(env_copy->expp, copy) == 0)
		(*check) = 1;
}

int	buildin_commands_proc(t_minishell *shell, t_tokens *tokens, t_env *env,
		int *std)
{
	char	*command;

	command = tokens->token;
	if (ft_cmp(command, "pwd"))
		return (pwd(shell, env), 1);
	if (ft_cmp(command, "cd"))
		return (cd(shell, tokens, env), 1);
	if (ft_cmp(command, "env"))
		return (env_buildin(shell, env), 1);
	if (ft_cmp(command, "export"))
		return (export(shell, tokens, env), 1);
	if (ft_cmp(command, "echo"))
		return (echo(shell, tokens), 1);
	if (ft_cmp(command, "unset"))
		return (unset(shell, tokens, env), 1);
	if (ft_cmp(command, "exit"))
		return (my_close_buildin(shell, std), my_exit(shell, tokens), 1);
	return (0);
}
