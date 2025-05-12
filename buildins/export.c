/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:21 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:38:22 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_minishell *shell, t_tokens *tokens, t_env *env)
{
	shell->exitcode = 0;
	if (tokens->next == NULL || export_print_check(tokens) == -1)
	{
		ft_print_expp(env, shell);
		return ;
	}
	export_var(shell, tokens, env);
}
