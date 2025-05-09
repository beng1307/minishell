/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:13:04 by bgretic           #+#    #+#             */
/*   Updated: 2024/10/26 15:17:25 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


/*ENUMS*/
typedef enum s_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,

	COMMAND,
	ARGS,
	REDIR
}	t_type;

/*STRUCTS*/
typedef struct s_error
{
	int	e;
}	t_error;

typedef	struct s_tokens
{
	char			*token;
	t_type			type;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_env
{
	char	*path;
	char	*expp; // refers to export_path;
	struct	s_env *next;
	struct	s_env *prev;
}	t_env;

typedef	struct s_cmd
{
	char			**command;
	char			**redir;
	t_type			type;
	bool			del_in_quotes;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_cmd_table
{
	t_cmd				*cmd;
	struct s_cmd_table	*prev;
	struct s_cmd_table	*next;
}	t_cmd_table;

typedef struct s_exec
{
	int			infile;
	int			outfile;
	int			cmd_count;
	int			loop;
	int			exit_status;
	int			check;
	int			prev_fd;
	int			redir_count;
	bool		master_splinter_is_king;
	bool		flag;
	char 		**envp;
	char		*path;
	char		**path_split;
	char		*heredoc;
} t_exec;

typedef struct s_minishell
{
	char		upd_env[PATH_MAX];
	char		**path;
	char		**argv;
    char    	*input;
    int     	exitcode;
	int			argc;
	bool		heredoc_quotes;
	t_tokens	*tokens;
	t_error		*error;
	t_exec		*exec;
}	t_minishell;


/*HELPER_FUNCTIONS*/
char	*sh_strjoin(char const *s1, char const *s2);


/*SINGLETON*/
t_minishell	*get_shell_data(void);


/*EXPANDER*/
void	expand(t_minishell *shell, t_tokens **tokens, t_env *env);


/*BUILDINS*/
void 	env_buildin(t_env *env);
void	pwd(t_minishell *shell, t_env *env);
void	cd(t_minishell *shell, t_env *env, char *path);
	/*ECHO*/
void	echo(t_minishell *shell, t_tokens *tokens);
void	print_tokens(t_tokens *tokens);
		/*EXPORT*/
void	export(t_minishell *shell, t_tokens *tokens, t_env *env);
void	export_var(t_minishell *shell, t_tokens *tokens, t_env *env);
char	**declare_env(t_minishell *shell);
		/*EXPORT HELPER*/
size_t	ft_strlen_to(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	bubble_sort(char **array, int count);
void	ft_print_array(char **array);
void	swap(char **a, char **b);
		/*EXPORT_HELPER_2*/
int		ft_mini_strrchr(char *str, int c);
t_env	*ft_lstnew_spec_env(void *content);
void	free_mem_c_arr(char **array, int index);
char	*ft_strjoin_expp(char const *s1, char const *s2);
			/*UNSET*/
void	unset(t_minishell *shell, t_tokens *tokens, t_env *env);


void	ft_free(char **str);
void	free_memory_array(char **array, int index);

/*SIGNAL_HANDLER*/
void	signal_handler(void);
void	handle_ctrl_d(void);
void	handle_ctrl_c(int signum);


/*TOKENIZING*/
t_tokens	*tokenize(char *shell_input);
bool		is_redirection_operator(int character);
int			tokenize_word(t_tokens **tokens, char *shell_input, int *index);
int			tokenize_redirection_operator(t_tokens **tokens, char *shell_input, int index);
void		type_the_tokens(t_tokens **tokens);

/*CMD_TABLE*/
t_cmd_table	*init_cmd_table(t_tokens *tokens);

t_cmd		*cmd_lstnew(void);
t_cmd		*cmd_lstlast(t_cmd *lst);
void		cmd_lstadd_back(t_cmd **lst, t_cmd *new);

t_cmd_table	*table_lstnew(t_cmd *new_cmd);
t_cmd_table	*table_lstlast(t_cmd_table *lst);
void		table_lstadd_back(t_cmd_table **lst, t_cmd_table *new);
/*QUOTES*/
bool	is_in_quotes(char current_char);


/*SYNTAX*/
int		just_whitespace(t_minishell *shell);
void	is_redirection(t_minishell *shell, int i, char *ident);
int		redirection_check_helper(t_minishell *shell, int i);
int		redirections_check(t_minishell *shell);
int		input_checks(t_minishell *shell);


/*SYNTAX_CHECKS*/
void	in_check_inp(t_minishell *shell, int i);
void	out_check_inp(t_minishell *shell, int i);
void	pipe_check_inp(t_minishell *shell, int i);
void	heredoc_check_inp(t_minishell *shell, int i);
void	append_check_inp(t_minishell *shell, int i);


/*SYNTAX_HELPER*/
int		skip_whitespaces(t_minishell *shell, int i);
int		helper_in(t_minishell *shell, int i, int j);
int		helper_out(t_minishell *shell, int i, int j);
int		helper_pipe(t_minishell *shell, int i, int j);
int		helper_app_here(t_minishell *shell, int i, int j);

/* SHELL LIST FUNCTIONS*/
t_tokens	*shell_lstnew(char *content);
void		shell_lstadd_back(t_tokens **lst, t_tokens *new);
void		shell_lstclear(t_tokens **lst, void (*del)(char **));

/*ENV LIST FUNCTIONS*/
t_env	*innit_env(char **envp);

t_env	*env_lstlast(t_env *lst);
t_env	*ft_lstnew_env(void *content);
t_env	*ft_lstnew_env_underscore(void *content);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstclear(t_env **lst, void (*del)(char **));
void	env_unset(t_env **lst);

void	update_env(t_minishell *shell, t_tokens *tokens, t_env *env);

int		ft_strcmp(const char *s1, const char *s2);
/*LIST HELPER*/
void	print_tokens(t_tokens *tokens);

/*INPUT_HANDLING*/
bool	check_quotes(t_minishell *shell);

/*FT_REALLOC*/
void    ft_realloc_path(t_minishell *shell, char **old_memory, size_t old_size, size_t new_size);
void    free_mem_c_arr(char **array, int index);

/*EXECUTION*/
char	*find_path_command(t_minishell *shell, char *arg);
char	*create_full_path(t_minishell *shell, char *arg);
int		child_process(t_minishell *shell, t_cmd *cmd,
		t_tokens *tokens, t_env *env);
int		execute_commands(t_minishell *shell, t_tokens *tokens,
		t_env *env, t_cmd_table *cmd_table);

/*EXECUTION_UTILS*/
int		execute_commands(t_minishell *shell, t_tokens *tokens,
		t_env *env, t_cmd_table *cmd_table);
int		command_count(t_cmd_table *cmd_table);
int		redir_count(t_cmd_table *cmd_table);
char 	**get_infile_outfile(t_minishell *shell, t_cmd *cmd, char **args);

/*EXECUTION_UTILS_2*/
int	check_for_slash(char **command);
char	**copy_envp(t_env *env, t_minishell *shell);

/*EXECUTION_FREE*/
void 	free_array(char **array);
void 	free_all_exec(t_minishell *shell, int check);
void	my_close(int *fd, t_minishell *shell);

/*HEREDOC*/
int		generate_heredoc_name(t_minishell *shell);
int		create_heredoc(t_cmd *cmd, t_minishell *shell, char *del);
char	**heredoc_cmd_table(t_cmd *cmd, t_minishell *shell, char **args);

/*REDIRECTIONS*/
int		set_flag_true(t_minishell *shell);
int		heredoc(t_cmd *cmd, t_minishell *shell);
int		input(t_cmd *cmd, t_minishell *shell);
int 	output(t_cmd *cmd, t_minishell *shell);
int 	append(t_cmd *cmd, t_minishell *shell);

int		buildin_commands(t_minishell *shell, t_tokens *tokens, t_env *env, char *command);

#endif
