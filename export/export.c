/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:41:27 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/18 14:42:27 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_invalid(t_minishell *shell, char *string)
{
	shell->exitcode = 1;
	write(2, "export: `", 9);
	ft_putstr_fd(string, 2);
	write(2, "': not a valid identifier\n", 26);
	shell->exp_valid = false;
}

int	full_export_check(char *string, t_minishell *shell)
{
	int	i;

	i = 0;
	if (string[i] == '=')
		return (export_invalid(shell, string), 1);
	while (string[i] != '\0' && string[i] != '=')
	{
		if (i == 0 && ft_isdigit(string[i]) == 1)
			return (export_invalid(shell, string), 1);
		if (string[i] != '_')
		{
			if (ft_isalnum(string[i]) == 0)
				return (export_invalid(shell, string), 1);
		}
		i++;
	}
	return (0);
}

int	expp_count(t_env *current)
{
	int	count;

	count = 0;
	while (current)
	{
		if (!current->expp)
		{
			if (current->next)
				current = current->next;
			else
				return (count);
		}
		current = current->next;
		count++;
	}
	return (count);
}

void	ft_print_expp(t_env *env, t_minishell *shell)
{
	t_env	*current;
	int		count;
	char	**expp_array;
	int		i;

	(void)shell;
	current = env;
	count = expp_count(current);
	i = 0;
	expp_array = ft_calloc(count + 1, sizeof(char *));
	if (!expp_array)
		terminator();
	current = env;
	while (i < count)
	{
		if (current->expp == NULL)
			current = current->next;
		expp_array[i] = current->expp;
		current = current->next;
		i++;
	}
	bubble_sort(expp_array, count);
	ft_print_array(expp_array);
	free(expp_array);
}

int	export_print_check(t_tokens *tokens_og)
{
	t_tokens	*tokens;

	tokens = tokens_og;
	while (tokens->next && tokens->type != BREAK_NODE)
	{
		tokens = tokens->next;
		if (tokens->type == WORD)
			return (1);
	}
	return (-1);
}
