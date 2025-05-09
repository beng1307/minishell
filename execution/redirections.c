#include "../minishell.h"

int	set_flag_true(t_minishell *shell)
{
	shell->exitcode = 1;
	shell->exec->flag = true;
	return (0);
}

int	heredoc(t_cmd *cmd, t_minishell *shell)
{
	if (generate_heredoc_name(shell) == 1)
		return (perror("Error_create_filename_heredoc"), set_flag_true(shell), 1);
	if (create_heredoc(cmd, shell, cmd->redir[1]) == 1)
		return (perror("Error_heredoc"), set_flag_true(shell), 1);
	shell->exec->infile = open(shell->exec->heredoc, O_RDONLY);
	if (shell->exec->infile == -1)
		return (perror(shell->exec->heredoc), set_flag_true(shell), 1);
	return (0);
}

int	input(t_cmd *cmd, t_minishell *shell)
{
	shell->exec->infile = open(cmd->redir[1], O_RDONLY);
	if (shell->exec->infile == -1)
	{
		shell->exitcode = 1;
		return (perror(cmd->redir[1]), 1);
	}
	return (0);
}

int output(t_cmd *cmd, t_minishell *shell)
{
	shell->exec->outfile = open(cmd->redir[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (shell->exec->outfile == -1)
	{
		shell->exitcode = 1;
		return (perror(cmd->redir[1]), 1);
	}
	return (0);
}

int append(t_cmd *cmd, t_minishell *shell)
{
	shell->exec->outfile = open(cmd->redir[1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (shell->exec->outfile == -1)
	{
		shell->exitcode = 1;
		return (perror(cmd->redir[1]), 1);
	}
	return (0);
}
