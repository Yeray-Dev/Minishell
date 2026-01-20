#include "minishell.h"

volatile sig_atomic_t handler = 0;

int main (int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell t_shell;

    init_signals();
    t_shell.our_envp = duplicate_envp(envp);
    
    while (1)
    {
        char *line;
        line = readline("MiniShell: > ");
        parser(line, &t_shell);
        t_shell.list_token.top = NULL;
    }
    return 0;
}