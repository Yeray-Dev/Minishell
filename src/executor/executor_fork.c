#include "minishell.h"

/*
Recorre todos los comandos y crea un fork para cada uno.
Si hay solo un builtin se ejecuta en el proceso padre.
*/
void launch_children(t_shell *sh, t_cmd *cmd_list, char **envp, int **pipes, int count)
{
    t_cmd *tmp;
    pid_t pid;
    int i;

    tmp = cmd_list;
    i = 0;
    while (tmp)
    {
        if (count == 1 && tmp->builtin_type != BI_NONE)
        {
            sh->exit_status = exec_builtin(sh, tmp);
            tmp = tmp->next;
            continue;
        }
        pid = fork();
        if (pid == 0)
            child_process(sh, tmp, pipes, i, count, envp);
        tmp = tmp->next;
        i++;
    }
}