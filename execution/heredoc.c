# include "../minishell.h"


int generate_heredoc_name(t_minishell *shell)
{
	int		pid;
	char	*string;

	pid = getpid();
	string = ft_itoa(pid);

	shell->exec->heredoc = ft_strjoin("/tmp/heredoc_", string);
	if (!shell->exec->heredoc)
	{
		free(string);
		shell->exitcode = 1;
		return (1);
	}
	free(string);
	return (0);
}

int create_heredoc(t_cmd *cmd,t_minishell *shell, char *del)
{
	char *line;

	if (shell->exec->infile != -1)
	{
		close(shell->exec->infile);
		shell->exec->infile = -1;
	}
	shell->exec->infile = open(shell->exec->heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (shell->exec->infile == -1)
	{
		shell->exitcode = 1;
		return (perror(shell->exec->heredoc), 1);
	}
	//if del in quotes means expander flag heredoc_quotes true -> not expand if false expand
	//if we have to expand i send to expander
	cmd->del_in_quotes = false;
	while (shell->exec->master_splinter_is_king)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		/* if (cmd->del_in_quotes == false)
		{
			line = expand_line();//->later
		} */
		write(shell->exec->infile, line, ft_strlen(line));
		write(shell->exec->infile, "\n", 1);
		free(line);
	}
	close(shell->exec->infile);
	return (0);
}

char	**heredoc_cmd_table(t_cmd *cmd, t_minishell *shell, char **args)
{
	t_cmd 		*cmd_cpy;
	char		**array;
	int			i;

	i = 0;
	cmd_cpy = cmd;
	while (cmd_cpy)
	{
		if (cmd_cpy->next && cmd_cpy->type == COMMAND && cmd_cpy->next->type == HEREDOC)
		{
			if (ft_strcmp(cmd_cpy->next->redir[0], "<<") == 0)
			{
				while(cmd_cpy->command[i] != NULL)
					i++;
				array = (char **)ft_calloc(i + 2, sizeof(char *));
				if (!array)
					return (perror ("allocation_error"), NULL);
				i = 0;
				while (cmd_cpy->command[i] != NULL)
				{
					array[i] = ft_strdup(cmd_cpy->command[i]);
					if (!array[i])
						return (free_memory_array(array, i), perror("allocation_error"), NULL);
					i++;
				}
				array[i] = ft_strdup(shell->exec->heredoc);
				if (!array[i])
					return (free_memory_array(array, i), perror ("allocation_error"), NULL);
				//free_array(args); ??
				return (	printf("wolverine is here\n"), array);
			}
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (args);
}

/* int	heredoc_cmd_table(t_cmd_table *cmd_table, t_minishell *shell)
{
	t_cmd_table *cmd_cpy;
	char		**array;
	int			i;

	i = 0;
	cmd_cpy = cmd_table;
	while (cmd_cpy)
	{
		if (cmd_cpy->cmd->type == COMMAND && cmd_cpy->cmd->next->type == REDIR)
		{
			if (ft_strcmp(cmd_cpy->cmd->next->redir[0], "<<") == 0)
			{
				while(cmd_cpy->cmd->command[i] != NULL)
					i++;
				array = (char **)ft_calloc(i + 2, sizeof(char *));
				if (!array)
					return (perror ("allocation_error"), 1);
				i = 0;
				while (cmd_cpy->cmd->command[i] != NULL)
				{
					array[i] = ft_strdup(cmd_cpy->cmd->command[i]);
					if (!array[i])
						return (free_memory_array(array, i), perror("allocation_error"), 1);
					i++;
				}
				array[i] = ft_strdup(shell->exec->heredoc);
				if (!array[i])
					return (free_memory_array(array, i), perror ("allocation_error"), 1);
				free_array(cmd_cpy->cmd->command);
				cmd_cpy->cmd->command = array;
				break ;
			}
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (0);
} */