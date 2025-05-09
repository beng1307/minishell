#include "../minishell.h"

void	type_the_tokens(t_tokens **tokens)
{
	t_tokens	*to_type;

	to_type = *tokens;
	while (to_type)
	{
		if (ft_cmp(to_type->token, "|"))
			to_type->type = PIPE;
		else if (ft_cmp(to_type->token, "<"))
			to_type->type = INPUT;
		else if (ft_cmp(to_type->token, ">"))
			to_type->type = OUTPUT;
		else if (ft_cmp(to_type->token, "<<"))
			to_type->type = HEREDOC;
		else if (ft_cmp(to_type->token, ">>"))
			to_type->type = APPEND;
		else
			to_type->type = WORD;
		to_type = to_type->next;
	}
}
