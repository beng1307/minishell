/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:43:14 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:15 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unexpected_token_newline(void)
{
	write(2, "syntax error near unexpected token `newline'\n", 45);
}

void	unexpected_token(t_minishell *shell)
{
	write(2, "syntax error near unexpected token `", 36);
	ft_putchar_fd(shell->input[shell->error->e], 2);
	if (shell->is_here_app == 1)
		ft_putchar_fd(shell->input[shell->error->e], 2);
	write(2, "'\n", 2);
}
