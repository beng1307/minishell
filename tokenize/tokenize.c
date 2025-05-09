#include "../minishell.h"

t_tokens	*tokenize(char *shell_input)
{
	t_tokens 	*tokens;
	int			index;

	index = 0;
	tokens = NULL;
	while (shell_input[index])
	{
		if ((shell_input[index] != ' ' && shell_input[index] != '\t')
			&& !is_redirection_operator(shell_input[index]))
			tokenize_word(&tokens, shell_input, &index);
		else if (shell_input[index] == '|'
			|| shell_input[index] == '<' || shell_input[index] == '>')
			index = tokenize_redirection_operator(&tokens, shell_input, index);
		index++;
	}
	type_the_tokens(&tokens);
	return (tokens);
}
