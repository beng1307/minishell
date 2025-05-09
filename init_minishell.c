#include "minishell.h"

t_minishell	*get_shell_data(void)
{
	static t_minishell	shell;

	return (&shell);
}