/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:12:39 by tdocekal          #+#    #+#             */
/*   Updated: 2024/10/26 15:19:41 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_command(t_minishell *shell, char *arg)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (shell->exec->envp[i] != NULL)
	{
		if (ft_strncmp(shell->exec->envp[i], "PATH=", 5) == 0)
		{
			while (shell->exec->envp[i][len] != '\0')
				len++;
			shell->exec->path = ft_substr(shell->exec->envp[i], 5, len);
			if (!shell->exec->path)
				return (perror("Allocation ERROR\n"), free_memory_array(shell->exec->envp, i), exit(1), NULL);
			break ;
		}
		i++;
	}
	if (shell->exec->path == NULL)
		return (NULL);
	shell->exec->path_split = ft_split(shell->exec->path, ':');
	if (!shell->exec->path_split)
		return (perror("Allocation ERROR\n"), free_all_exec(shell, 1), exit(1), NULL);
	return (create_full_path(shell, arg));
}

char	*ft_strjoin_exec(char const *s1, char const *s2)
{
	char	*news;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2) +2;
	news = (char *)malloc(i * sizeof(char));
	if (news == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		news[j] = s1[j];
		j++;
	}
	news[j++] = '/';
	while (s2[k] != '\0')
	{
		news[j] = s2[k];
		j++;
		k++;
	}
	news[j] = '\0';
	return (news);
}

char	*create_full_path(t_minishell *shell, char *arg)
{
	int		i;
	char	*full_path;

	i = 0;
	while (shell->exec->path_split[i] != NULL)
	{
		full_path = ft_strjoin_exec(shell->exec->path_split[i], arg);
		if (!full_path)
			return (perror("Allocation ERROR\n"), free_all_exec(shell, 1), exit(1), NULL);
		
		if (access(full_path, X_OK) == 0)
			return (free_all_exec(shell, 0), full_path);
		ft_free(&full_path);
		i++;
	}
	return (free_all_exec(shell, 0), ft_free(&full_path), NULL);
}

int	execute(t_minishell *shell, t_env *env, char **args, t_tokens *tokens)
{
	char *path;
	t_tokens *tok_cpy;

	tok_cpy = tokens;
	while (tok_cpy && ft_strcmp(tok_cpy->token, args[0]) != 0)
		tok_cpy = tok_cpy->next;
	if (buildin_commands(shell, tok_cpy, env, args[0]) == 0)
		{
			if (check_for_slash(args) == 1)
				path = args[0];
			else
				path = find_path_command(shell, args[0]);
			if (!path)
			{
				path = args[0];
				shell->exec->check = 1;
				ft_putstr_fd(path, 2);
				write(2, ": command not found\n", 20);
				ft_free(&path);
				return (free_all_exec(shell, 1), exit(127), 1);
			}
			execve(path, args, shell->exec->envp);
			perror(path);
			if (shell->exec->check == 1)
				ft_free(&path);
			return (free_all_exec(shell, 1), exit(1), 1);
		}
	return (0);
}
char **set_args(t_cmd *cmd)
{
	t_cmd *copy;

	copy = cmd;
	while (copy && copy->type != COMMAND)
		copy = copy->next;
	return (copy->command);
}

int	child_process(t_minishell *shell, t_cmd *cmd,
t_tokens *tokens, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd_cpy;
	char **args;

	cmd_cpy = cmd;
	args = set_args(cmd_cpy);
	args = get_infile_outfile(shell, cmd_cpy, args);
	if (args == NULL)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipe error"), 1);
	pid = fork();
	if (pid == -1)
		return (my_close(fd, shell), 1);
	if (pid == 0)
	{
		close(fd[0]);
		//printf("shell->exec->infile here %d, out : %d, prev: %d, fd[0]: %d, fd[1]: %d, shell exec loop %d, cmd count:%d\n", shell->exec->infile, shell->exec->outfile, shell->exec->prev_fd, fd[0], fd[1], shell->exec->loop, shell->exec->cmd_count);
		if (shell->exec->infile != -1)
		{	
			if (dup2(shell->exec->infile, STDIN_FILENO) == -1)
				return (perror("dup2, infile"), free_all_exec(shell, 1), my_close(fd, shell), exit(1), 1);
		}
		else if (shell->exec->loop > 0 && shell->exec->prev_fd != -1)
			if (dup2(shell->exec->prev_fd, STDIN_FILENO) == -1)
				return (perror("dup2, connect"), free_all_exec(shell, 1), my_close(fd, shell), exit(1), 1);
		if (shell->exec->outfile != -1)
		{
			if (dup2(shell->exec->outfile, STDOUT_FILENO) == -1)
				return (close(fd[1]), perror("dup2, out"), free_all_exec(shell, 1), my_close(fd, shell), exit(1), 1);
		}
		else if (shell->exec->loop < (shell->exec->cmd_count - 1))
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				return (perror("dup2 fd[1]"), free_all_exec(shell, 1), my_close(fd, shell), exit(1), 1);
		close (fd[1]);
		//my_close(fd, shell);
		//set to fds to -1
		return (execute(shell, env, args, tokens));
	}
	else
	{
		shell->exec->prev_fd = fd[0];
		my_close(fd, shell);
		if (shell->exec->loop == (shell->exec->cmd_count - 1))
		{
			close(fd[1]);
			close(fd[0]);
			waitpid(pid, &shell->exec->exit_status, 0);
			if (WIFEXITED(shell->exec->exit_status))
				shell->exitcode = WEXITSTATUS(shell->exec->exit_status);
		}
		return (0);
	}	
}

int	execute_commands(t_minishell *shell, t_tokens *tokens,
t_env *env, t_cmd_table *cmd_table)
{
	t_cmd_table	*cmd_cpy;
	t_cmd		*cmd;
	t_tokens 	*crnt_token;

	shell->exec->cmd_count = command_count(cmd_table);
	shell->exec->redir_count = redir_count(cmd_table);
	crnt_token = tokens;
	cmd_cpy = cmd_table;
	shell->exec->loop = 0;
	shell->exec->envp = copy_envp(env, shell);
 	// int i = 0;
 	// while (cmd_cpy)
	// {
	// 	cmd = cmd_cpy->cmd;
	// 	while(cmd)
	// 	{
	// 		if (cmd->command)
	// 			printf("%s, %s\n", cmd->command[i], cmd->command[i + 1]);
	// 		if (cmd->redir)
	// 			printf("%s, %s\n", cmd->redir[i], cmd->redir[i + 1]);
	// 		cmd = cmd->next;
	// 	}
	// 	cmd_cpy = cmd_cpy->next;
	// } 
	// cmd_cpy = cmd_table; 
	while (cmd_cpy && shell->exec->loop < (shell->exec->cmd_count))
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == COMMAND)
			{
				while (crnt_token && ft_strcmp(crnt_token->token, cmd->command[0]) != 0)
					crnt_token = crnt_token->next;
				if ((shell->exec->cmd_count == 1) && shell->exec->redir_count == 0 &&
				(buildin_commands(shell, crnt_token, env, cmd->command[0]) == 1))
					return (0);
				cmd = cmd_cpy->cmd; //infinity loop here !!
				if (child_process(shell, cmd, tokens, env) == 1)
					return (perror("CHILD_PROCESS_FAILED"), 1);
				shell->exec->loop++;
				break ;
			}
			cmd = cmd->next;
		}
		cmd_cpy = cmd_cpy->next;
	}
	if (shell->exec->prev_fd != -1)
		close (shell->exec->prev_fd);
	return (0);
}

