#include "../minishell.h"

void	my_close(int *fd, t_minishell *shell)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	if (shell->exec->outfile != -1)
	{
		close(shell->exec->outfile);
		shell->exec->outfile = -1;
	}
/* 	if (shell->exec->loop == (shell->exec->cmd_count - 1) && shell->exec->prev_fd != -1)
		close (shell->exec->prev_fd); */
}

void free_array(char **array)
{
	int i;

	i = 0;
	if (!(array || *array))
		return ;
	while (array[i] != NULL)
	{
		ft_free(&array[i]);
		i++;
	}
}

void free_all_exec(t_minishell *shell, int check)
{
	if (shell->exec->path)
		ft_free(&shell->exec->path);
	if (shell->exec->path_split)
		free_array(shell->exec->path_split);
	if (shell->exec->envp && check != 0)
		free_array(shell->exec->envp);
}