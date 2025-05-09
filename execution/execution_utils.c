#include "../minishell.h"

char	**get_infile_outfile(t_minishell *shell, t_cmd *cmd, char **args)
{
	t_cmd *cmd_copy;

	cmd_copy = cmd;
	while (cmd)
	{
		if (cmd->type == HEREDOC)
		{
			if (ft_strncmp(cmd->redir[0], "<<", 2) == 0)
			{
				if (heredoc(cmd, shell) == 1)
					return (NULL);
				args = heredoc_cmd_table(cmd_copy, shell, args);
				if (args == NULL)
					return (set_flag_true(shell), NULL);
			}
		}
		if (cmd->type == INPUT)
		{
			if (ft_strncmp(cmd->redir[0], "<", 1) == 0)
				if (input(cmd, shell) == 1)
					return (NULL);
		}
		if (cmd->type == OUTPUT)
		{
			if (ft_strncmp(cmd->redir[0], ">", 1) == 0)
			{
				if (output(cmd, shell) == 1)
					return (NULL);
			}
		}
		if (cmd->type == APPEND)
		{
			if (ft_strncmp(cmd->redir[0], ">>", 2) == 0)
				if (append(cmd, shell) == 1)
					return (NULL);
		}
		cmd = cmd->next;
	}
	return (args);
}

int command_count(t_cmd_table *cmd_table)
{
	t_cmd_table *cmd_cpy;
	t_cmd		*cmd;
	int			count;

	cmd_cpy = cmd_table;
	count = 0;
	while (cmd_cpy)
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == COMMAND)
				count++;
			cmd = cmd->next;
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (count);
}

int redir_count(t_cmd_table *cmd_table)
{
		t_cmd_table *cmd_cpy;
	t_cmd		*cmd;
	int			count;

	cmd_cpy = cmd_table;
	count = 0;
	while (cmd_cpy)
	{
		cmd = cmd_cpy->cmd;
		while (cmd)
		{
			if (cmd->type == REDIR)
				count++;
			cmd = cmd->next;
		}
		cmd_cpy = cmd_cpy->next;
	}
	return (count);
}

/* int	get_infile_outfile(t_tokens *tokens, t_minishell *shell, t_cmd_table *cmd_table, char **args)
{
	t_tokens *tok_cpy;

	tok_cpy = tokens;
	while (tok_cpy)
	{
		if (tok_cpy->type == HEREDOC)
		{
			if (generate_heredoc_name(shell) == 1)
			{
				perror("Error_create_filename_heredoc");
				shell->exec->flag = true;
			}
			if (create_heredoc(shell, tok_cpy->next->token) == 1)
			{
				perror("Error_heredoc");
				shell->exec->flag = true;
			}
			shell->exec->infile = open(shell->exec->heredoc, O_RDONLY);
			if (shell->exec->infile == -1)
			{
				shell->exitcode = 1;
				perror(shell->exec->heredoc);
				shell->exec->flag = true;
			}
			if (heredoc_cmd_table(cmd_table, shell) == 1)
			{
				shell->exitcode = 1;
				shell->exec->flag = true;
			}
			tok_cpy = tok_cpy->next;
		}
		else if (tok_cpy->type == INPUT)
		{
			shell->exec->infile = open(tok_cpy->next->token, O_RDONLY);
			if (shell->exec->infile == -1)
			{
				shell->exitcode = 1;
				perror(tok_cpy->next->token);
				shell->exec->flag = true;
			}
			tok_cpy = tok_cpy->next;
		}
		if (tok_cpy->type == OUTPUT && tok_cpy->next->next == NULL)
		{
			shell->exec->outfile = open(tok_cpy->next->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (shell->exec->outfile == -1 || shell->exec->flag == true)
			{
				shell->exitcode = 1;
				if (shell->exec->flag == true)
					perror("Error_infile");
				else
					perror(tok_cpy->next->token);
				return (1);
			}
			tok_cpy = tok_cpy->next;
		}
		tok_cpy = tok_cpy->next;
	}
	return (0);
}  */
