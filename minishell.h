/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:13:04 by bgretic           #+#    #+#             */
/*   Updated: 2025/01/08 17:27:29 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

/*GLOBAL*/
extern int	g_signal_heredoc;

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
	REDIR,
	BREAK_NODE,
	EMPTY_EXPANSION,
	EMPTY
}						t_type;

/*STRUCTS*/
typedef struct s_error
{
	int					e;
}						t_error;

typedef struct s_tokens
{
	char				*token;
	t_type				type;
	struct s_tokens		*prev;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	char				*path;
	char				*expp;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_cmd
{
	char				**command;
	char				**redir;
	t_type				type;
	bool				del_in_quotes;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_cmd_table
{
	t_cmd				*cmd;
	struct s_cmd_table	*prev;
	struct s_cmd_table	*next;
}						t_cmd_table;

typedef struct s_exec
{
	int					infile;
	int					outfile;
	int					cmd_count;
	int					redir_count;
	int					justr_count;
	int					loop;
	int					exit_status;
	int					check;
	int					prev_fd;
	bool				master_splinter_is_king;
	bool				flag;
	bool				to_free_exec;
	bool				path_flag;
	bool				redir_flag;
	char				**args;
	char				**envp;
	char				*path;
	char				**path_split;
	char				*heredoc;
	pid_t				pid;
	t_tokens			*crnt_token;
	t_cmd_table			*cmd_cpy;
	t_cmd				*cmd;
}						t_exec;

typedef struct s_minishell
{
	char				*upd_env;
	char				**path;
	char				**argv;
	char				*input;
	char				*new_token;
	int					exitcode;
	int					argc;
	int					is_here_app;
	int					shell_loop;
	bool				is_interactive;
	bool				blank;
	bool				heredoc_quotes;
	bool				unset;
	bool				exp_valid;
	bool				fu_dog_goat;
	bool				unequal_quotes;
	bool				called_from_exit;
	t_tokens			*tokens;
	t_env				*env;
	t_cmd_table			*table;
	t_error				*error;
	t_exec				*exec;
}						t_minishell;

/*INITIATION*/
void					init_exec(t_minishell *shell);
void					init_shell(t_minishell *shell, int argc, char **argv);

void					init_tokens_and_table(t_minishell *shell, t_env *env, \
						t_tokens **tokens, t_cmd_table **cmd_table);

void					init_shell_2(t_minishell *shell);
void					is_shell_interactive(t_minishell *shell);
/*TERMINATORS*/
void					soft_terminator(void);
void					terminator(void);

/*FREE*/
void					free_content(t_minishell *shell);
void					error_message(t_minishell *shell, char *string,
							int nbr);

/*HELPER_FUNCTIONS*/
char					*sh_strjoin(const char *s1, char const *s2, int i,
							int j);

/*SINGLETON*/
t_minishell				*get_shell_data(void);

/*EXPANDER*/
void					expand(t_tokens **tokens, t_env *env,
							t_minishell *shell);
void					expand_line(char **line, t_minishell *shell,
							t_env *env);
void					word_splitting(t_tokens **tokens);
void					copy_char_to_new_token(char **new_token,
							t_tokens *token_cpy, int new_token_length,
							int *index);
bool					expand_variable(char **curr_new_token,
							t_tokens **token_cpy, t_env *env, int *index);
void					expand_exit_code(char **curr_new_token,
							int shell_exitcode, int *index);
bool					cmd_is_echo_singleton(t_tokens *token_cpy);
void					init_expand_vars(t_tokens **token_copy,
							t_tokens **tokens, bool *empty_expansion, \
							char **new_token);
void					free_and_check(char **curr_new_token,
							char *new_token, t_tokens **token_cpy);

/*BUILDINS*/
void					env_buildin(t_minishell *shell, t_env *env);
void					pwd(t_minishell *shell, t_env *env);
void					cd(t_minishell *shell, t_tokens *token, t_env *env);

void					set_exit_flag(t_minishell *shell);

/*CD_HELPER*/
void					go_to_path(t_minishell *shell, t_env *env, char *path,
							char *old_cwd);
void					go_to_old_path(t_minishell *shell, t_env *env);
t_env					*get_old_pwd_node(t_env *env);
t_env					*get_pwd_node(t_env *env);
void					go_to_home_directory(t_minishell *shell, t_env *env,
							char *old_cwd);
int						count_cd_args(t_tokens *tokens);
void					error_wrong_path(char *path);

/*ECHO*/
void					echo(t_minishell *shell, t_tokens *tokens);

/*EXPORT*/
void					export(t_minishell *shell, t_tokens *tokens,
							t_env *env);
int						full_export_check(char *string, t_minishell *shell);
void					ft_print_expp(t_env *env, t_minishell *shell);
void					export_invalid(t_minishell *shell, char *string);
/*EXPORT_PRINT*/
void					ft_print_expp(t_env *env, t_minishell *shell);
int						export_print_check(t_tokens *tokens_og);
int						expp_count(t_env *current);
int						full_export_check(char *string, t_minishell *shell);
void					export_invalid(t_minishell *shell, char *string);

/*EXPORT_VAR*/
void					export_var(t_minishell *shell, t_tokens *tokens,
							t_env *env);

/*EXPORT HELPER*/
size_t					ft_strlen_to(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
void					bubble_sort(char **array, int count);
void					ft_print_array(char **array);
void					swap(char **a, char **b);

/*EXPORT_HELPER_2*/
int						ft_mini_strrchr(char *str, int c);
t_env					*ft_lstnew_spec_env(void *content);
char					*ft_strjoin_expp(char const *s1, char const *s2);
char					*ft_own_trim_equal(char *cpy);

/*UNSET*/
void					unset(t_minishell *shell, t_tokens *tokens, t_env *env);
void					set_exit_code(t_minishell *shell, int nbr);
void					ft_free(char **str);
char					*ft_strtrim_declare_x(char *copy);

/*EXIT*/
void					my_exit(t_minishell *shell, t_tokens *tokens);
long					ft_atoi_long(const char *str, t_minishell *shell,
							t_tokens *current);
bool					check_long_overflow(long sum, long nbr, long sign);
void					exit_message(t_minishell *shell, t_tokens *tokens);
void					free_memory_array(char **array, int index);

/*EXIT_UTILS*/
int						is_string_numeric(char *string);
int						is_string_with_white(char *string);
int						is_string_just_arit(char *string);
int						is_string_mult_arit(char *string);
int						ft_isdigit_exit(int arg);

/*SIGNAL_HANDLER*/
void					ignore_signals(void);
void					signal_handler(void);
void					heredoc_signal_handler(void);
void					handle_ctrl_d(t_minishell *shell);
void					handle_ctrl_c(int signum);

/*TOKENIZING*/
t_tokens				*tokenize(char *shell_input);
bool					is_redirection_operator(int character);
int						tokenize_word(t_tokens **tokens, char *shell_input,
							int *index);
int						tokenize_redirection_operator(t_tokens **tokens,
							char *shell_input, int index);
void					type_the_tokens(t_tokens **tokens);

/*CMD_TABLE*/
t_cmd_table				*init_cmd_table(t_tokens *tokens);
void					adapter(t_tokens **tokens, t_cmd_table **table);

t_cmd_table				*table_lstnew(t_cmd *new_cmd);
t_cmd_table				*table_lstlast(t_cmd_table *lst);
void					table_lstadd_back(t_cmd_table **lst, t_cmd_table *new);
void					table_lstclear(
							t_cmd_table **lst,
							void (del)(t_cmd **, void (del)(char ***)));
void					allocate_command(t_cmd **lastlst,
							t_tokens *tokens_copy);

t_cmd					*cmd_lstnew(void);
t_cmd					*cmd_lstlast(t_cmd *lst);
void					cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void					cmd_lstclear(t_cmd **lst, void (del)(char ***));

/*QUOTES*/
bool					is_quote(int character);
bool					check_quotes(t_minishell *shell);
void					check_heredoc_quotes(t_cmd **lastlst);
bool					is_in_quotes(char current_char);
bool					quote_found(char *token);
bool					is_delimeter_quote(char current_char);
int						quote_free_token_length(char *token);
void					remove_quotes(char **token);
bool					is_in_singlequotes(char current_char, int index);

/*SYNTAX*/
int						just_whitespace(t_minishell *shell);
void					is_redirection(t_minishell *shell, int i, char *ident);
int						redirection_check_helper(t_minishell *shell,
							int i, bool in_quotes);
int						redirections_check(t_minishell *shell);
int						input_checks(t_minishell *shell);

/*SYNTAX_CHECKS*/
void					in_check_inp(t_minishell *shell, int i, int j);
void					out_check_inp(t_minishell *shell, int i, int j);
void					pipe_check_inp(t_minishell *shell, int i, int j);
void					heredoc_check_inp(t_minishell *shell, int i, int j);
void					append_check_inp(t_minishell *shell, int i, int j);

/*SYNTAX_HELPER*/
int						skip_whitespaces(t_minishell *shell, int i);
int						helper_in(t_minishell *shell, int i, int j);
int						helper_out(t_minishell *shell, int i, int j);
int						helper_pipe(t_minishell *shell, int i, int j);
int						helper_app_here(t_minishell *shell, int i, int j);

/*SYNTAX_HELPER_2*/
void					check_append_inp_helper(t_minishell *shell, int i);
void					check_heredoc_inp_helper(t_minishell *shell, int i);
void					check_out_inp_helper(t_minishell *shell, int i);
void					check_in_inp_helper(t_minishell *shell, int i);
/*ADDITIONAL_SYNTAX*/
void					unexpected_token_newline(void);
void					unexpected_token(t_minishell *shell);

/* SHELL LIST FUNCTIONS*/
t_tokens				*shell_lstnew(char *content);
t_tokens				*shell_lstlast(t_tokens *lst);
void					shell_lstadd_back(t_tokens **lst, t_tokens *new);
void					shell_lstadd_between(t_tokens **lst, t_tokens *new);
void					shell_lstclear(t_tokens **lst, void (del)(char **));

/*ENV LIST FUNCTIONS*/
t_env					*innit_env(t_minishell *shell, char **envp);

t_env					*env_lstlast(t_env *lst);
t_env					*ft_lstnew_env(void *content);
t_env					*ft_lstnew_env_underscore(void *content);
void					env_lstadd_back(t_env **lst, t_env *new);
void					env_lstclear(t_env **lst, void (*del)(char **));
void					env_unset(t_env **lst);

void					update_env(t_minishell *shell, t_tokens *tokens,
							t_env *env);

int						ft_strcmp(const char *s1, const char *s2);

/*LIST HELPER*/
void					print_tokens(t_tokens *tokens);

/*INPUT_HANDLING*/
bool					check_quotes(t_minishell *shell);

/*EXECUTION*/
int						child_process(t_minishell *shell, t_cmd *cmd,
							t_tokens *tokens, t_env *env);
int						execute_commands(t_minishell *shell, t_tokens *tokens,
							t_env *env, t_cmd_table *cmd_table);

int						execute(t_minishell *shell, t_tokens *tokens,
							t_env *env);
void					dot_cases(t_minishell *shell, int index);

/*EXECUTION CHILD_PROCESS*/
int						child_process(t_minishell *shell, t_cmd *cmd,
							t_tokens *tokens, t_env *env);
void					wait_function(t_minishell *shell, pid_t pid, int *fd);

/*EXECUTION_BUILDINS*/
int						buildin_process(t_minishell *shell, t_tokens *tokens,
							t_env *env, t_cmd *cmd);
int						dup2_buildin_process(t_minishell *shell, int *std);
int						is_buildin(char *arg);
char					**set_args_buildin(t_cmd *cmd);

/*EXECUTION PATH*/
char					*find_path_command(t_minishell *shell, char *arg);
char					*ft_strjoin_exec(char const *s1, char const *s2);
char					*create_full_path(t_minishell *shell, char *arg);

/*EXECUTION_UTILS*/
int						command_count(t_cmd_table *cmd_table);
int						redir_count(t_cmd_table *cmd_table);
int						get_infile_outfile(t_minishell *shell, t_cmd *cmd,
							t_env *env);
int						is_there_another_word(t_tokens *current);
int						buildin_commands_exec(t_minishell *shell,
							t_tokens *tokens, t_env *env, char *command);

/*EXECUTION_UTILS_2*/
int						check_for_slash(char **command, int index);
char					**copy_envp(t_env *env);
int						how_many_cmds(t_cmd *cmd);
int						is_there_a_pipe(t_cmd_table *cmd_table);

int						just_redir_count(t_minishell *shell,
							t_cmd_table *cmd_table, bool flag, int count);

/*EXECUTION_UTILS_3*/;
void					directory_check(t_minishell *shell, char *path);
void					error_message(t_minishell *shell, char *string,
							int nbr);
char					**set_args(t_minishell *shell, t_cmd *cmd);

/*EXECUTION_UTILS_4*/
int						execute_redir(t_minishell *shell, t_env *env);
int						execute_single_redir(t_minishell *shell, t_env *env);
void					set_fu_dog(t_minishell *shell);

/*EXECUTION_FREE*/
void					free_array(char ***array);
void					free_all_exec(t_minishell *shell, int check);
void					my_close(int *fd, t_minishell *shell);
void					my_close_buildin(t_minishell *shell, int *std);
void					my_close_main_exec(t_minishell *shell);

/*EXECUTION_FREE_2*/
void					exit_execution(t_minishell *shell,
							char *path, int index);
void					free_args(t_minishell *shell);
void					free_envp(t_minishell *shell);

/*HEREDOC*/
int						generate_heredoc_name(t_minishell *shell);
int						create_heredoc_line(char **line,
							t_minishell *shell, char *del);
int						create_heredoc(t_cmd *cmd, t_minishell *shell,
							t_env *env, char *del);
char					*get_home(t_env *env);
char					*get_var_content(t_env *env, char *to_search,
							bool *empty_expansion);
int						get_var_len(char *token);
void					print_heredoc_message(t_minishell *shell, char *del);
int						open_heredoc(t_minishell *shell);
char					*heredoc_get_var_content(t_env *env, char *to_search);

/*REDIRECTIONS*/
int						set_flag_true(t_minishell *shell);
int						heredoc(t_cmd *cmd, t_minishell *shell, t_env *env);
int						input(t_cmd *cmd, t_minishell *shell);
int						output(t_cmd *cmd, t_minishell *shell);
int						append(t_cmd *cmd, t_minishell *shell);

int						buildin_commands(t_minishell *shell, t_tokens *tokens,
							t_env *env, char *command);

void					wait_out_of_gio(void);

/*UTILS*/
char					*get_last_word_token(t_tokens *tokens);
void					michael_checkson(t_env *env_copy,
							size_t *check, char *copy);
void					close_heredoc(t_minishell *shell);
int						buildin_commands_proc(t_minishell *shell,
							t_tokens *tokens, t_env *env, int *std);

#endif
