#include "../minishell.h"

int	just_whitespace(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->input[i] == ' ' || shell->input[i] == '\t')
		i++;
	if (shell->input[i] == '\0' || shell->input[i] == '\n')
		return (1);
	return (0);
}

void	is_redirection(t_minishell *shell, int i, char *ident)
{
	if (ft_strncmp(ident, "heredoc", 7) == 0)
		heredoc_check_inp(shell, ++i);
	else if (ft_strncmp(ident, "append", 6) == 0)
		append_check_inp(shell, ++i);
	else if (ft_strncmp(ident, "in", 2) == 0)
		in_check_inp(shell, i);
	else if (ft_strncmp(ident, "out", 3) == 0)
		out_check_inp(shell, i);
	else if (ft_strncmp(ident, "pipe", 4) == 0)
		pipe_check_inp(shell, i);
}

int	redirection_check_helper(t_minishell *shell, int i)
{
	int	j;

	j = 0;
	if ((shell->input[i] == '<') && (shell->input[i + 1] == '<'))
	{
		is_redirection(shell, i, "heredoc");
		j++;
	}
	else if ((shell->input[i] == '>') && (shell->input[i + 1] == '>'))
	{
		is_redirection(shell, i, "append");
		j++;
	}
	else if (shell->input[i] == '>')
		is_redirection(shell, i, "out");
	else if (shell->input[i] == '<')
		is_redirection(shell, i, "in");
	else if (shell->input[i] == '|')
		is_redirection(shell, i, "pipe");
	return (j);
}

int redirections_check(t_minishell *shell)
{
	int	i;

	shell->error->e = -999;
	i = 0;
	while (shell->input && (shell->input[i] != '\n' && shell->input[i] != '\0'))
	{
		while (shell->input[i] == ' ' || shell->input[i] == '\t')
			i++;
		i += redirection_check_helper(shell, i);
		if (shell->error->e != -999)
		{
			if (shell->input[shell->error->e] == '\n')
				ft_printf("syntax error near unexpected token : newline\n");
			else if (shell->input[shell->error->e] == '\0')
				ft_printf("syntax error near unexpected token : newline\n");
			else
				ft_printf("syntax error near unexpected token : %c\n",\
				shell->input[shell->error->e]);
			rl_on_new_line();
			shell->exitcode = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	input_checks(t_minishell *shell)
{
	if (just_whitespace(shell) == 1)
	{
		rl_on_new_line();
		shell->exitcode = 0;
		return (1);
	}
	if (redirections_check(shell) == 1)
		return (1);
	return (0);
}
