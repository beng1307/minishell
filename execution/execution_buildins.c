/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_buildins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:39:01 by tdocekal          #+#    #+#             */
/*   Updated: 2025/01/08 16:54:47 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**set_args_buildin(t_cmd *cmd)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy->type != COMMAND)
		copy = copy->next;
	if (copy->type == COMMAND)
		return (copy->command);
	return (NULL);
}

int	is_buildin(char *arg)
{
	if (ft_strcmp(arg, "pwd") == 0)
		return (1);
	if (ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "export") == 0)
		return (1);
	if (ft_strcmp(arg, "echo") == 0)
		return (1);
	if (ft_strcmp(arg, "unset") == 0)
		return (1);
	if (ft_strcmp(arg, "exit") == 0)
		return (1);
	if (ft_strcmp(arg, "cd") == 0)
		return (1);
	return (0);
}

int	dup2_buildin_process(t_minishell *shell, int *std)
{
	if (shell->exec->infile != -1)
	{
		if (dup2(shell->exec->infile, STDIN_FILENO) == -1)
			return (my_close_buildin(shell, std), error_message(shell,
					"DUP2_BUILD_IN", 1), 1);
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		if (dup2(shell->exec->outfile, STDOUT_FILENO) == -1)
			return (my_close_buildin(shell, std), error_message(shell,
					"DUP2_BUILD_OUT", 1), 1);
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
	return (0);
}

int	dup2_back_to_std(t_minishell *shell, int *std)
{
	if (dup2(std[0], STDIN_FILENO) == -1)
		return (my_close_buildin(shell, std),
			perror("DUP2->BACK_TO_NORMAL_STDIN"), 1);
	close(std[0]);
	if (dup2(std[1], STDOUT_FILENO) == -1)
		return (my_close_buildin(shell, std),
			perror("DUP2->BACK_TO_NORMAL_STDOUT"), 1);
	close(std[1]);
	return (0);
}

int	buildin_process(t_minishell *shell, t_tokens *tokens, t_env *env,
		t_cmd *cmd)
{
	t_tokens	*tok_cpy;
	t_cmd		*cmd_cpy;
	int			std[2];

	std[0] = dup(STDIN_FILENO);
	if (std[0] == -1)
		return (1);
	std[1] = dup(STDOUT_FILENO);
	if (std[1] == -1)
		return (close(std[0]), 1);
	cmd_cpy = cmd;
	tok_cpy = tokens;
	shell->exec->args = set_args_buildin(cmd_cpy);
	if (shell->exec->args == NULL)
		return (my_close_buildin(shell, std), 1);
	if (get_infile_outfile(shell, cmd_cpy, env) == -1)
		return (my_close_buildin(shell, std), 0);
	while (tok_cpy && ft_strcmp(tok_cpy->token, shell->exec->args[0]) != 0)
		tok_cpy = tok_cpy->next;
	if (dup2_buildin_process(shell, std) == 1)
		return (1);
	buildin_commands_proc(shell, tok_cpy, env, std);
	if (dup2_back_to_std(shell, std) == 1)
		return (1);
	return (0);
}
