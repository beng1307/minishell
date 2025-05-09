#include "minishell.h"

//displays prompt on a new line
void	handle_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_ctrl_backslash(int signum)
{
	if (signum == SIGQUIT)
		return ;
} 

//create a proper exiting function
//with history clear later
void	handle_ctrl_d(void)
{
		exit(0);
}

void	signal_handler(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
}