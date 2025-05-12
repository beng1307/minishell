/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:38:34 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/30 16:33:37 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_code(t_minishell *shell, int nbr)
{
	shell->exitcode = nbr;
}

void	set_exit_flag(t_minishell *shell)
{
	shell->called_from_exit = true;
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	pwd_path_not_found(t_minishell *shell)
{
	char	*pwd_env;
	char	cwd[_PC_PATH_MAX];

	pwd_env = getenv("PWD");
	if (pwd_env)
		ft_printf("%s\n", pwd_env);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s\n", cwd);
		else
		{
			perror("getcwd() error");
			shell->exitcode = 1;
		}
	}
}

void	pwd(t_minishell *shell, t_env *env)
{
	t_env	*current;

	current = env;
	shell->exitcode = 0;
	while (current != NULL)
	{
		if ((*current->path) && ft_strncmp(current->path, "PWD=", 4) == 0)
		{
			if (ft_strlen(current->path) == 4)
				break ;
			ft_printf("%s\n", &current->path[4]);
			return ;
		}
		current = current->next;
	}
}
