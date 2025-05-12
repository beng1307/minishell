/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:44:04 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/22 19:00:42 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_minishell *shell)
{
	shell->exec->infile = -1;
	shell->exec->outfile = -1;
	shell->exec->prev_fd = -1;
	shell->exec->cmd_count = 0;
	shell->exec->justr_count = 0;
	shell->exec->loop = 0;
	shell->exec->exit_status = 0;
	shell->exec->check = 0;
	shell->exec->master_splinter_is_king = true;
	shell->exec->flag = false;
	shell->exec->to_free_exec = false;
	shell->exec->path_flag = false;
	shell->exec->redir_flag = false;
	shell->exec->args = NULL;
	shell->exec->path = NULL;
	shell->exec->envp = NULL;
	shell->exec->path_split = NULL;
	shell->exec->heredoc = NULL;
	shell->exec->crnt_token = NULL;
	shell->exec->cmd_cpy = NULL;
	shell->exec->cmd = NULL;
}

void	init_shell(t_minishell *shell, int argc, char **argv)
{
	static t_error	error;
	static t_exec	exec;

	shell->argc = argc;
	shell->argv = argv;
	shell->input = NULL;
	shell->path = NULL;
	shell->upd_env = NULL;
	shell->exitcode = 0;
	shell->is_here_app = 0;
	shell->shell_loop = 0;
	shell->is_interactive = true;
	shell->heredoc_quotes = true;
	shell->blank = false;
	shell->unset = false;
	shell->exp_valid = true;
	shell->fu_dog_goat = true;
	shell->unequal_quotes = false;
	shell->called_from_exit = false;
	shell->error = &error;
	shell->exec = &exec;
	shell->argc++;
	init_exec(shell);
	init_shell_2(shell);
}

void	init_shell_2(t_minishell *shell)
{
	shell->tokens = NULL;
	shell->env = NULL;
	shell->table = NULL;
	shell->new_token = NULL;
}

void	is_shell_interactive(t_minishell *shell)
{
	if (isatty(STDIN_FILENO) == 1)
		shell->is_interactive = true;
	else
		shell->is_interactive = false;
}

void	init_tokens_and_table(t_minishell *shell, t_env *env,
		t_tokens **tokens, t_cmd_table **cmd_table)
{
	*tokens = tokenize(shell->input);
	if (!*tokens)
		return (ft_printf("Tokenizing didn't work out properly!"),
			terminator());
	expand(tokens, env, shell);
	word_splitting(tokens);
	*cmd_table = init_cmd_table(*tokens);
	if (!*cmd_table)
		return (ft_printf("CMD_TABLE_ERROR\n"), terminator());
	adapter(tokens, cmd_table);
}
