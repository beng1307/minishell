#include "minishell.h"

int parsing(t_minishell *shell, t_tokens *tokens)
{
	t_tokens	*current_token;

	current_token = tokens;
	while (current_token != NULL)
	{
		current_token = current_token->next;
	}
}