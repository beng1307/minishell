/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:44:28 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/23 19:29:52 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_heredoc = 1;

void	history_commands(t_minishell *shell, t_env *env)
{
	t_env	*current;

	current = env;
	env = current;
	if (check_quotes(shell) == false)
		shell->unequal_quotes = true;
	if (*shell->input && just_whitespace(shell) == 0
		&& shell->unequal_quotes == false)
		add_history(shell->input);
	else
		shell->blank = true;
}

int	buildin_commands(t_minishell *shell, t_tokens *tokens, t_env *env,
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
		return (my_exit(shell, tokens), 1);
	return (0);
}

int	minishell_main_loop(t_minishell *shell, t_tokens *tokens,
t_cmd_table *cmd_table, t_env *env)
{
	const char	*prompt;

	prompt = "-> ";
	while (1)
	{
		signal_handler();
		shell->input = readline(prompt);
		if (!shell->input)
			handle_ctrl_d(shell);
		if (g_signal_heredoc == 1)
			shell->exitcode = 130;
		shell->shell_loop++;
		history_commands(shell, env);
		if (input_checks(shell) != 1 && shell->blank == false)
		{
			init_tokens_and_table(shell, env, &shell->tokens, &cmd_table);
			tokens = shell->tokens;
			shell->table = cmd_table;
			execute_commands(shell, tokens, env, cmd_table);
			update_env(shell, tokens, env);
		}
		soft_terminator();
		free_that(&shell->input);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	t_tokens	*tokens;
	t_cmd_table	*cmd_table;
	t_env		*env;

	shell = get_shell_data();
	tokens = NULL;
	cmd_table = NULL;
	init_shell(shell, argc, argv);
	is_shell_interactive(shell);
	env = innit_env(shell, envp);
	shell->env = env;
	tokens = NULL;
	minishell_main_loop(shell, tokens, cmd_table, env);
	return (0);
}
