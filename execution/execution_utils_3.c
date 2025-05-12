/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:06 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/02 22:51:45 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_arg_count(t_cmd *copy, t_cmd *cmd, int idx)
{
	int	count;

	count = 0;
	while (copy)
	{
		idx = 0;
		if (copy->type == COMMAND)
		{
			while (copy->command[idx++] != NULL)
				count++;
		}
		copy = copy->next;
	}
	copy = cmd;
	return (count);
}

char	**set_args_main_loop(t_minishell *shell,
	t_cmd *copy, int count, int idx)
{
	shell->exec->args = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!shell->exec->args)
		return (free_all_exec(shell, 1), terminator(), NULL);
	count = 0;
	while (copy)
	{
		if (copy->type == COMMAND)
		{
			shell->exec->args[idx++] = ft_strdup(copy->command[count++]);
			if (!shell->exec->args[idx - 1])
				return (free_memory_array(shell->exec->args, (idx - 1)),
					free_array(&shell->exec->envp), terminator(), NULL);
			while (copy->command[count] != NULL)
			{
				shell->exec->args[idx++] = ft_strdup(copy->command[count]);
				if (!shell->exec->args[idx - 1])
					return (free_memory_array(shell->exec->args, (idx - 1)),
						free_array(&shell->exec->envp), terminator(), NULL);
				count++;
			}
		}
		count = 0;
		copy = copy->next;
	}
	return (shell->exec->args);
}

char	**set_args(t_minishell *shell, t_cmd *cmd)
{
	t_cmd	*copy;
	int		count;
	int		idx;

	copy = cmd;
	idx = 0;
	count = set_arg_count(copy, cmd, idx);
	idx = 0;
	return (set_args_main_loop(shell, copy, count, idx));
}

void	error_message(t_minishell *shell, char *string, int nbr)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		write(2, &string[i++], 1);
	shell->exitcode = nbr;
}

int	buildin_commands_exec(t_minishell *shell, t_tokens *tokens, t_env *env,
		char *command)
{
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
		return (free_all_exec(shell, 1), my_exit(shell, tokens), 1);
	return (0);
}
