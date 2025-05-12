NAME = minishell
CC = cc 
CFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory
FLAGS = -lreadline -lc
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)/libft.a
OBJS_DIR = ./objs/
SRCS = minishell.c \
initiation.c \
buildins/env.c \
buildins/echo.c \
buildins/exit.c \
buildins/export.c \
buildins/exit_utils.c \
buildins/pwd.c \
buildins/unset.c \
buildins/cd.c \
buildins/go_to_old_path.c \
buildins/go_to_path_utils.c \
buildins/go_to_path.c \
cmd_table/adapter.c \
cmd_table/cmd_list_functions.c \
cmd_table/init_cmd_table_1.c \
cmd_table/init_cmd_table_2.c \
cmd_table/table_list_functions.c \
cmd_table/quote_functions_1.c \
cmd_table/quote_functions_2.c \
expander/expander_1.c \
expander/expander_2.c \
expander/expander_3.c \
expander/heredoc_expander_1.c \
expander/heredoc_expander_2.c \
expander/word_splitting.c \
export/export.c \
export/export_var.c \
export/export_helper.c \
export/export_helper_2.c \
terminators/terminator.c \
terminators/soft_terminator.c \
tokenize/shell_list_functions.c \
tokenize/tokenize_functions.c \
tokenize/tokenize.c \
tokenize/type_the_tokens.c \
utils/shell_strjoin.c \
utils/signal_handling.c \
utils/init_minishell.c \
utils/check_quotes.c \
utils/utils.c \
env/env_functions.c \
env/env_update.c \
syntax_checks/syntax_checks.c \
syntax_checks/syntax_helper.c \
syntax_checks/syntax_helper_2.c \
syntax_checks/syntax_helper_3.c \
syntax_checks/syntax.c \
execution/execution.c \
execution/execution_execute_1.c \
execution/execution_execute_2.c \
execution/execution_child_process_1.c \
execution/execution_child_process_2.c \
execution/execution_buildins.c \
execution/execution_path.c \
execution/execution_utils.c \
execution/execution_utils_2.c \
execution/execution_utils_3.c \
execution/execution_utils_4.c \
execution/execution_free.c \
execution/execution_free_2.c \
execution/heredoc_1.c \
execution/heredoc_2.c \
execution/redirections.c \



OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Text

BOLD = \033[1m
UNDERLINE = \033[4m
RESET = \033[0m

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FLAGS)
	@echo "$(CYAN)MINISHELL COMPILED!$(DEF_COLOR)"
	@echo "$(UNDERLINE)$(MAGENTA)$(BOLD)Created Excecutable MINISHELL!$(RESET)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⠛⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠀⣠⣶⣶⣄⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⣀⣶⣿⣿⣿⣿⣿⣆⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠁$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠁⢀⣤⣶$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠁⢀⣠⣾⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠋⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠈⠉⠉⠙⠛⠛⠻⢿⣿⡿⠟⠁⠀⣀⣴⣿⣿⣿⣿⣿⠟$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⣉⣡⠀⣠⣴⣶⣶⣦⠄⣀⡀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⡿⢃⣾$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⣾⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣠⣾⡟⢡⣾⣿⣿⣿⡿⢋⣴⣿⡿⢀⣴⣾⣿⣿⣿⣿⣿⣿⣿⢡⣾⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠃⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣼⣿⡟⣰⣿⣿⣿⣿⠏⣰⣿⣿⠟⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢚⣛⢿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⠸⣿⠟⢰⣿⣿⣿⣿⠃⣾⣿⣿⠏⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⣾$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠻⠻⠃⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢉⣴⣿⣿⣿⣿⡇⠘⣿⣿⠋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡘⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⣿⣿⣿⣿⠁⢀⣀⠀⢀⣾⣿⣿⣿⣿⣿⣿⠟⠉⠉⠉⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣌$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⡿⠁⣀⣤⡀⠀⠈⠻⢿⠀⣼⣿⣷⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⠟⠛⠙⠃⠀⣿⣿⣿⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⡿⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠁⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⠟⠁⢀⣴⣶⣶⣾⣿⣿⣿⣿⣶⡐⢦⣄⠀⠀⠈⠛⢿⣿⣿⣿⣿⡀⠀⠀⠀⠀⢀⣼⡿⢛⣩⣴⣶⣶⣶⣶⣶⣶⣭⣙⠻⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠁⠀⣴⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣦⡙⠻⣶⣄⡀⠀⠈⠙⢿⣿⣷⣦⣤⣤⣴⣿⡏⣠⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣌⠻⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⣿⠋⣠⠔⠀⠀⠻⣿⣿⣿⣿⢉⡳⢦⣉⠛⢷⣤⣀⠀⠈⠙⠿⣿⣿⣿⣿⢸⣿⡄⠻⣿⣿⠟⡈⣿⣿⣿⣿⣿⢉⣿⣧⢹⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⡇⠠⡇⠀⠀⠀⠀⣿⣿⣿⣿⢸⣿⣷⣤⣙⠢⢌⡛⠷⣤⣄⠀⠈⠙⠿⣿⣿⣿⣿⣷⣦⣴⣾⣿⣤⣙⣛⣛⣥⣾⣿⣿⡌⣿⣿⣿⣷⣤⣀⣀⣀⣠⣴⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⣷⡀⠡⠀⠀⠀⣰⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣦⣌⡓⠤⣙⣿⣦⡄⠀⠈⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⣿⣿⣶⣤⣴⣾⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣷⠀⣶⡄⠀⠈⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢃⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⣿⣿⣿⠟⠻⣿⣿⡏⣉⣭⣭⡘⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⡇⢸⡇⢠⡀⠈⠙⠋⠉⠉⠉⠉⠛⠫⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⠛⣿⣿⣀⣀⣾⡿⢀⣿⣿⣿⢻⣷⣦⢈⡙⠻⢿⣿⣿⣿⣿⣿⣿⣿⠀⣿⡇⢸⡇⢸⣿⠀⣦⠀⠀⠶⣶⣦⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⢸⣿⣿⣦⣈⡛⠿⠟⣋⣤⣾⣿⣿⣿⣸⣿⣿⢸⡇⢰⡆⢈⡙⠻⢿⣿⣿⣿⠀⢿⡇⢸⡇⢸⣿⢠⣿⡇⣿⡆⢈⡙⠻⠧⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⠀⠀⣝⠛⢿⣿⣿⣿⣿⣿⣿⠟⣁⠀⠀⢈⠛⠿⢸⣇⢸⡇⢸⡇⣶⣦⣌⡙⠻⢄⡀⠁⠘⠇⠘⣿⢸⣿⡇⣿⡇⢸⡛⠷⣦⣄⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⡆⠀⠈⠳⢶⣤⣍⡉⠉⣩⣤⣤⡉⠻⢶⣤⣀⠂⠀⠉⠘⠇⢸⡇⣿⣿⣿⣿⣷⣦⣍⡑⠢⣄⠀⠈⠈⠻⠇⣿⡇⢸⣿⣷⣾⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣷⣦⣄⡀⠈⠉⠛⠶⢄⡉⠻⠿⣷⣦⣌⡙⠷⢶⣄⡀⠀⠈⠁⠙⢿⣿⣿⣿⣿⣿⣿⣷⣦⣍⡒⠤⣀⠀⠈⠃⢸⣿⣿⣿⣿⣷⠀⢸⣿⣿⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⠿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀⠈⠉⠂⠄⢙⣿⣿⣷⣦⣈⠙⠳⢦⣄⡀⠠⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣌⡐⠄⢸⣿⣿⣿⣿⣿⡇⠀⣿⠿⣿⣿⣿⣿⣷⣌⠻⣿⣿⣿⡿⢰⣦⣤$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣄⡀⠀⠀⠀⠉⠛⠛⠛⠿⠷⣤⣈⠛⠷⢤⣈⡂⢄⡉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣌⡛⠿⣿⣿⡇⠀⢿⣷⣌⡛⠿⠿⠏⣼⣷⣤⣉⣉⣀⣼⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠀⢀⣤⣶⣦⣤⣤⣄⡈⠙⠻⠖⠀⣉⣩⣤⣤⣤⣤⣤⣤⣀⡈⠉⠙⠻⣿⣿⣿⣿⣶⡄⠉⠀⠀⣸⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⣾⣿⣿⣿⣿⣿⣿⣿⠀⠀⣴⣿⣿⣿⣿⣿⠟⣩⣽⣿⣿⣿⣷⣦⣀⠀⠙⢻⣿⣿⠇⠀⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⠏⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠉⠻⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠘⣿⣿⡿⣡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣦⡀⠀⠸⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"
	@echo "$(CYAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢀⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢀⣙⣟⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣘⣛⣻⣦⢀⣀⣙⣛⣛⣛⣛⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(DEF_COLOR)"

$(LIBFT):
	@echo "$(YELLOW)Building PROJECT including libft libary.....$(DEF_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR)
$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
#	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rdf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)MINISHELL && LIBFT object files cleaned!$(DEF_COLOR)"	

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean                                                                      
	@echo "$(YELLOW)          ⣀⠤⠒⠈⠉⠉⠐⠢⠐⠈⠉⠉⠲⣄         $(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⠀⠀⡴⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⠀⡴⠁⠀⠀⣠⠤⢤⣀⡀⢀⡀⠀⠀⠀⠀⠀⠀⠣⡀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⠛⡲⠁⠀⡜⠁⠀⠀⠉⠀⠀⠘⢆⡵⡐⣄⠀⠀⠀⢈⡱⠂⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⢰⣀⣠⠜⠁⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡈⠛⢏⠉⠉⠉⠦⣀⣠⠆⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⢨⢇⠀⠀⠀⢀⡇⠏⢉⠝⠓⢨⠀⠀⢸⠕⠛⠫⡉⢹⣄⠀⠀⠀⠀⡜⡀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠈⢿⣦⡀⢠⢻⡉⡗⢺⠒⠄⢰⠋⠉⠹⡒⠦⠀⡗⠺⢩⠑⡄⢀⡼⡞⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠈⠳⢍⣸⡬⢇⠑⠚⠓⠒⣅⡀⠀⣀⢸⠒⠚⠒⠂⠼⡴⣁⠥⠊⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⠀⡇⠑⢚⠀⠀⠀⠔⠀⠈⠉⠀⠈⢆⠀⠀⠈⡖⠃⡸⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⠀⡸⠇⡜⡄⠀⣌⢴⠈⠡⠭⠈⢑⡄⣃⠀⠰⢃⡸⠇⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⠀⠀⢀⣀⠼⠒⢣⡀⠀⠀⠈⠉⠉⠉⠁⠀⠘⢀⡟⠪⢅⡀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⡠⠔⠉⠀⡀⢠⠃⣈⣑⣲⣄⣉⣒⣁⠠⣒⣊⠁⢱⠀⠀⠈⠓⢦⡀⠀⠀$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⡰⠊⠈⠢⣠⠊⠀⠸⠋⠀⠀⠀⠈⠑⠟⠊⠁⠀⠀⠈⠻⠀⠈⢢⡠⠊⠈⠳⡄$(DEF_COLOR)"
	@echo "$(YELLOW)⠊⠈⠳⡄⡰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⡀⡠⠊⠉$(DEF_COLOR)"
	@echo "$(YELLOW)⠀⠀⠀⣸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠃⠀⠀⠀⠀⠀⠰⠰⠒⠒⠒⢟⡀⠀⠀$(DEF_COLOR)"                      
	@echo "$(UNDERLINE)$(YELLOW)$(BOLD)ICH NUR PUTZEN$(RESET)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for MINISHELL$(DEF_COLOR)"
	@echo "$(GREEN)	⠀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⠀⡴⠋⠉⡊⢁⠀⠀⢬⠀⠉⠋⠈⠥⠤⢍⡛⠒⠶⣄⡀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⣾⠥⠀⠀⠊⢭⣾⣿⣷⡤⠀⣠⡀⡅⢠⣶⣮⣄⠉⠢⠙⡆⠀⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⣠⡾⣁⡨⠴⠢⡤⣿⣿⣿⣿⣿⠸⡷⠙⣟⠻⣯⣿⣟⣃⣠⡁⢷⣄⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⡼⡙⣜⡕⠻⣷⣦⡀⢙⠝⠛⡫⢵⠒⣀⡀⠳⡲⢄⣀⢰⣫⣶⡇⡂⠙⡇$(DEF_COLOR)"
	@echo "$(GREEN)⢸⡅⡇⠈⠀⠀⠹⣿⣿⣷⣷⣾⣄⣀⣬⣩⣷⠶⠧⣶⣾⣿⣿⣿⡷⠁⣇⡇$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠳⣅⢀⢢⠡⠀⡜⢿⣿⣿⡏⠑⡴⠙⣤⠊⠑⡴⠁⢻⣿⣿⣿⠇⢀⡞⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠘⢯⠀⡆⠀⠐⡨⡻⣿⣧⣤⣇⣀⣧⣀⣀⣷⣠⣼⣿⣿⣿⠀⢿⠀⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠈⢧⡐⡄⠀⠐⢌⠪⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢸⠀⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⠀⠙⢾⣆⠠⠀⡁⠘⢌⠻⣿⣿⠻⠹⠁⢃⢹⣿⣿⣿⡇⡘⡇⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⠀⠀⠀⠈⠛⠷⢴⣄⠀⢭⡊⠛⠿⠿⠵⠯⡭⠽⣛⠟⢡⠃⡇⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠲⠬⣥⣀⡀⠀⢀⠀⠀⣠⡲⢄⡼⠃⠀$(DEF_COLOR)"
	@echo "$(GREEN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠓⠒⠒⠒⠋⠉⠀⠀⠀$(DEF_COLOR)"

.PHONY: all clean fclean re
