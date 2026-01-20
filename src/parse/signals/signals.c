#include "minishell.h"

void init_signals(void)
{
    set_signal(SIGINT, handler_readline);
    set_signal(SIGQUIT, SIG_IGN);

}