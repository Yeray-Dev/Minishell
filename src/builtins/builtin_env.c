#include "minishell.h"

extern char **environ;

int builtin_env(t_cmd *cmd)
{
    int i;

    (void)cmd;
    i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return (0);
}
