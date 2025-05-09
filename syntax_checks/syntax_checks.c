#include "../minishell.h"

void	in_check_inp(t_minishell *shell, int i)
{
	int	j;

	j = i - 1;
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '>'
			|| shell->input[i] == '<')
		{
			shell->error->e = i;
			return ;
		}
		i = j + 1;
	}
	if (helper_in(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0' 
		|| shell->input[i] == '|' || shell->input[i] == '>')
		shell->error->e = i;
}

void	out_check_inp(t_minishell *shell, int i)
{
	int	j;

	j = i - 1;
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			return ;
		}
		i = j + 1;
	}
	if (helper_out(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '<')
		shell->error->e = i;
}

void	pipe_check_inp(t_minishell *shell, int i)
{
	int	j;

	j = i - 1;
	if (j == -1)
	{
		shell->error->e = i;
		return ;
	}
	if (helper_pipe(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '<'
		|| shell->input[j] == '>')
		shell->error->e = i;
}

void	append_check_inp(t_minishell *shell, int i)
{
	int	j;

	j = i - 2;
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			return ;
		}
		i = j + 2;
	}
	if (helper_app_here(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '<'
		|| shell->input[j] == '>')
		shell->error->e = i;
}

void	heredoc_check_inp(t_minishell *shell, int i)
{
	int	j;

	j = i - 2;
	if (j == -1)
	{
		i = skip_whitespaces(shell, ++i);
		if (shell->input[i] == '\n' || shell->input[i] == '\0'
			|| shell->input[i] == '|' || shell->input[i] == '<'
			|| shell->input[i] == '>')
		{
			shell->error->e = i;
			return ;
		}
		i = j + 2;
	}
	if (helper_app_here(shell, i, j) == 1)
		return ;
	i = skip_whitespaces(shell, ++i);
	if (shell->input[i] == '\n' || shell->input[i] == '\0'
		|| shell->input[i] == '|' || shell->input[i] == '<'
		|| shell->input[j] == '>')
		shell->error->e = i;
}