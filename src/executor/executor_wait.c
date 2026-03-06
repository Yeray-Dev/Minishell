#include "minishell.h"

/*
Cierra todos los pipes en el proceso padre y libera memoria.
*/
static void close_and_free(int **pipes, int count)
{
    int i;

    if (!pipes)
        return ;
    i = 0;
    while (i < count - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

/*
Espera a que todos los procesos hijos terminen
y guarda el exit status del último comando.
*/
void wait_and_close(int **pipes, int count, t_shell *sh)
{
    int status;

    close_and_free(pipes, count);
    while (count > 0)
    {
        wait(&status);
        if (WIFEXITED(status))
            sh->exit_status = WEXITSTATUS(status);
        else
            sh->exit_status = 1;
        count--;
    }
}