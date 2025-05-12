/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execute_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:21 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/15 18:45:15 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dot_cases(t_minishell *shell, int index)
{
	if (ft_strcmp(shell->exec->args[index], ".") == 0)
	{
		write(2, ".: command not found\n", 21);
		shell->exitcode = 127;
		shell->called_from_exit = true;
		free_all_exec(shell, 1);
		terminator();
	}
	if (ft_strcmp(shell->exec->args[index], "..") == 0)
	{
		write(2, "..: command not found\n", 22);
		shell->exitcode = 127;
		shell->called_from_exit = true;
		free_all_exec(shell, 1);
		terminator();
	}
}
