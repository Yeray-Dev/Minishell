#include "minishell.h"

/*
Crea todos los pipes necesarios para un pipeline.
Número de pipes = número de comandos - 1
*/
int **create_pipes(int count)
{
    int **pipes;
    int i;

    if (count < 2)
        return (NULL);
    pipes = malloc(sizeof(int *) * (count - 1));
    if (!pipes)
        return (NULL);
    i = 0;
    while (i < count - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) < 0)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }
    return (pipes);
}

/*
Cierra todos los pipes en un proceso
cuando ya no son necesarios.
*/
void close_all_pipes(int **pipes, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}
