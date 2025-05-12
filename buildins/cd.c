/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:50:38 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/23 19:34:49 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cd_args(t_tokens *tokens)
{
	if (!tokens || tokens->type == BREAK_NODE || tokens->type == INPUT
		|| tokens->type == OUTPUT || tokens->type == HEREDOC
		|| tokens->type == APPEND)
		return (0);
	return (1 + count_cd_args(tokens->next));
}

void	error_wrong_path(char *path)
{
	write(2, "bash: cd: ", 10);
	perror(path);
}

void	cd(t_minishell *shell, t_tokens *token, t_env *env)
{
	char	cwd[PATH_MAX];

	shell->exitcode = 0;
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("getcwd");
		shell->exitcode = 1;
		return ;
	}
	if (!token->next || token->next->type == BREAK_NODE)
		go_to_home_directory(shell, env, cwd);
	else if (count_cd_args(token) > 2)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		shell->exitcode = 1;
	}
	else if (ft_cmp(token->next->token, "-"))
		go_to_old_path(shell, env);
	else
		go_to_path(shell, env, token->next->token, cwd);
}
