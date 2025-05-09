#include "minishell.h"

const char *update_prompt(t_minishell *shell)
{
	const char *prompt_red;
	const char *prompt_green;
	const char *prompt_blue;

	prompt_green = "\033[1;32m  🐕‍🦺 Barbarian_HERE_DOGS 🐕‍🦺> \033[0m";
	prompt_red = "\033[1;31m  🐕‍🦺 Barbarian_HERE_DOGS 🐕‍🦺> \033[0m";
	prompt_blue = "\033[1;34m  🐕‍🦺 Barbarian_HERE_DOGS 🐕‍🦺> \033[0m";

	if (shell->exitcode != 0)
		return (prompt_red);
	return (prompt_green);
}

void	history_commands(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	t_env	*current;

	current = env;
	env = current;
	if (*shell->input && just_whitespace(shell) == 0)
		add_history(shell->input);
	if (shell->exitcode != 0)
		return ;
	if (ft_strncmp(shell->input, "clear_history", 13) == 0)
	{
		rl_clear_history();
		ft_printf("Command history cleared\n");
	}
	else if (ft_strncmp(shell->input, "exit", 4) == 0)
	{
		shell_lstclear(&tokens, ft_free);
		free(shell->input);
		rl_clear_history();
		exit (0);
	}
}

int	buildin_commands(t_minishell *shell, t_tokens *tokens, t_env *env, char *command)
{
	if (strncmp(command, "cd", 2) == 0)
		return (cd(shell, env, ));
	if (strncmp(command, "pwd", 3) == 0)
		return (pwd(shell, env), 1);
	if (strncmp(command, "env", 3) == 0)
		return (env_buildin(env), 1);
	if (strncmp(command, "export", 6) == 0)
		return (export(shell, tokens, env), 1);
	if (strncmp(command, "echo", 4) == 0)
		return (echo(shell, tokens), 1);
	if (strncmp(command, "unset", 5) == 0)
		return (unset(shell, tokens, env), 1);
	return (0);
}

void innit_exec(t_minishell *shell)
{
	shell->exec->infile = -1;
	shell->exec->outfile = -1;
	shell->exec->prev_fd = -1;
	shell->exec->cmd_count = 0;
	shell->exec->loop = 0;
	shell->exec->exit_status = 0;
	shell->exec->check = 0;
	shell->exec->master_splinter_is_king = true;
	shell->exec->flag = false;
	shell->exec->envp = NULL;
	shell->exec->path = NULL;
	shell->exec->path_split = NULL;
	shell->exec->heredoc = NULL;

}
void	innit_shell(t_minishell *shell, int argc, char **argv, t_tokens *tokens)
{
	static t_error		error;
	static t_exec exec;

	shell->argc = argc;
	shell->argv = argv;
	shell->input = NULL;
	shell->path = NULL;
	ft_bzero(shell->upd_env, PATH_MAX);
	shell->exitcode = 0;
	shell->heredoc_quotes = true;
	shell->error = &error;
	shell->exec = &exec;
	shell->argc++;
	shell->tokens = tokens;
	innit_exec(shell);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt;
	t_minishell	*shell;
	t_tokens	*tokens;
	t_cmd_table	*cmd_table;
	t_env		*env;

	shell = get_shell_data();
	tokens = NULL;
	innit_shell(shell, argc, argv, tokens);
	env = innit_env(envp);
	tokens = NULL;
	prompt = "\033[1;32m  🐕‍🦺 Barbarian_HERE_DOGS 🐕‍🦺> \033[0m";
	signal_handler();
	while(1)
	{
		shell->input = readline(prompt);
		if (!shell->input)
			handle_ctrl_d();
		history_commands(shell, tokens, env);
		//if (input_checks(shell) != 1)
		//{
			tokens = tokenize(shell->input);
			if (!tokens)
				return (ft_printf("Tokenizing didn't work out properly!"), 1);
			expand(shell, &tokens, env);
			cmd_table = init_cmd_table(tokens);
			// //add protection
			//buildin_commands(shell, tokens, env, shell->input);
			execute_commands(shell, tokens, env, cmd_table);
			update_env(shell, tokens, env); //_=usr/bin/env ! multiple _=env in env!!! //everytime i export var add _=env
		//}
		prompt = update_prompt(shell);
		free(shell->input);
	}
	return (0);
}

/*INTEGRATE SHLLVL VARIABLE*/

//is a tty kriegt fd zu sehen ob es was ist ??
//start is tty is fd 0 is fd 0 file ? is fd 0 stdin if fd 0 is file get next line read file if not 0 its a tty 
/*FUCHECK -i readline SUPRESS IGNORE FUNCTION*/
//Herdoc << EOF wird expandet wenn nicht in quotes wenn << "EOF" dann nicht expandet
