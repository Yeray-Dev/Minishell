#include "minishell.h"

/*
Cuenta cuantos comandos hay en la lista del parser.
Se usa para saber cuantos pipes crear y cuantos forks hacer.
*/
static int count_cmds(t_cmd *cmd)
{
    int count;

    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

/*
Función principal del executor.
Crea pipes, lanza procesos hijos y espera su terminación.
*/
int executor(t_shell *sh, t_cmd *cmd_list, char **envp)
{
    int count;
    int **pipes;

    count = count_cmds(cmd_list);
    pipes = create_pipes(count);
    launch_children(sh, cmd_list, envp, pipes, count);
    wait_and_close(pipes, count, sh);
    return (sh->exit_status);
}