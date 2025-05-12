/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:37 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/22 20:08:04 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	terminator(void)
{
	t_minishell	*shell;

	shell = get_shell_data();
	free_content(shell);
	if (shell->env)
		env_lstclear(&shell->env, free_that);
	if (shell->called_from_exit == false)
	{
		write(2, "ALLOCATION_ERROR\n", 17);
		shell->exitcode = 1;
	}
	if (shell->upd_env)
		free_that(&shell->upd_env);
	if (shell->input)
		free(shell->input);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(shell->exitcode);
}
