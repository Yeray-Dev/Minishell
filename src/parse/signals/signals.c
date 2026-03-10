#include "minishell.h"


void init_signals(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;  // Suprime el ^C, ^\ etc
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
    set_signal(SIGINT, handler_readline);
    set_signal(SIGQUIT, SIG_IGN);

}