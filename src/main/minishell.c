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
        handler = 0;
        char *line;
        line = readline("MiniShell: > ");
        if (line == NULL)
            break;
        if (handler == 1)
        {
            t_shell.exit_status = 1; //* COMPROBAR

            handler = 0;
            free(line);
            continue;
        }
        parser(line, &t_shell);
        execute_commands(&t_shell);
        free_cmd_list(&t_shell.cmd_list);
        free(line);
    }
    return 0;
}