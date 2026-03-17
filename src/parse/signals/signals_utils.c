#include "minishell.h"

void	handler_sigint(int sig)
{
	(void)sig;
	g_handler = 2;
}

void	handler_sigquit(int sig)
{
	(void)sig;
	g_handler = 3;
}

void	handler_readline(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_on_new_line ();
	rl_replace_line ("", 0);
	rl_redisplay ();
	g_handler = 1;
}

void	set_signal(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(sig, &sa, NULL);
}
