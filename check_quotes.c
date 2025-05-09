#include "minishell.h"

bool	check_quotes(t_minishell *shell)
{
	int	index;
	int	single_quotes;
	int	double_quotes;

	index = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (shell->input[index])
	{
		if (shell->input[index] == '\'')
			single_quotes++;
		else if (shell->input[index] == '\"')
			double_quotes++;
		index++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}