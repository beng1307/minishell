#include "../minishell.h"

int	skip_whitespaces(t_minishell *shell, int i)
{
	while (shell->input[i] == ' ' || shell->input[i] == '\t')
		i++;
	return (i);
}

int	helper_in(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '>' || shell->input[j] == '|')
		{
			shell->error->e = i;
			return (1);
		}
	}
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if ((shell->input[j] == '>') || (shell->input[j] == '|')
		|| (shell->input[j] == '<' && (j + 1) != i))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}

int	helper_out(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|')
		{
			shell->error->e = i;
			return (1);
		}
	}
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if ((shell->input[j] == '<') || (shell->input[j] == '|')
		|| (shell->input[j] == '>' && (j + 1) != i))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}

int	helper_pipe(t_minishell *shell, int i, int j)
{
	if (i == 1)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|'
			|| shell->input[j] == '>')
		{
			shell->error->e = i;
			return (1);
		}
	}
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if ((shell->input[j] == '<') || (shell->input[j] == '|'
			|| shell->input[j] == '>') || (j == -1))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}

int	helper_app_here(t_minishell *shell, int i, int j)
{
	if (i == 2)
	{
		if (shell->input[j] == '<' || shell->input[j] == '|'
			|| shell->input[j] == '>')
		{
			shell->error->e = i;
			return (1);
		}
	}
	while (shell->input[j] == ' ' || shell->input[j] == '\t')
		j--;
	if ((shell->input[j] == '<') || (shell->input[j] == '|'
			|| shell->input[j] == '>'))
	{
		shell->error->e = i;
		return (1);
	}
	return (0);
}