/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:40:01 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/23 19:31:58 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_envp(t_env *current, t_env *env)
{
	int	count;

	count = 0;
	while (current)
	{
		current = current->next;
		while (current && current->path == NULL)
			current = current->next;
		count++;
	}
	current = env;
	return (count);
}

char	**copy_envp(t_env *env)
{
	t_env	*current;
	char	**envp;
	int		count;

	current = env;
	envp = NULL;
	count = count_envp(current, env);
	envp = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!envp)
		return (terminator(), NULL);
	count = 0;
	while (current)
	{
		while (current && current->path == NULL)
			current = current->next;
		if (!current)
			break ;
		envp[count] = ft_strdup(current->path);
		if (!envp[count])
			return (free_memory_array(envp, count), terminator(), NULL);
		current = current->next;
		count++;
	}
	return (envp);
}

int	how_many_cmds(t_cmd *cmd)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy)
	{
		if (copy->type == COMMAND)
			return (1);
		copy = copy->next;
	}
	return (0);
}

int	is_there_a_pipe(t_cmd_table *cmd_table)
{
	t_cmd_table	*cmd_cpy;
	int			count;

	cmd_cpy = cmd_table;
	count = 0;
	while (cmd_cpy)
	{
		count++;
		cmd_cpy = cmd_cpy->next;
	}
	if (count > 1)
		return (1);
	return (0);
}

int	just_redir_count(t_minishell *shell, t_cmd_table *cmd_table,
	bool flag, int count)
{
	t_cmd_table	*cmd_cpy;
	t_cmd		*cmd;

	cmd_cpy = cmd_table;
	while (cmd_cpy)
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == COMMAND)
			{
				flag = true;
				break ;
			}
			cmd = cmd->next;
		}
		if (flag == false)
			count++;
		if (flag == false && shell->exec->cmd_count == 1 && !cmd_cpy->next)
			shell->exec->redir_flag = true;
		flag = false;
		cmd_cpy = cmd_cpy->next;
	}
	return (count);
}
