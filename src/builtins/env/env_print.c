#include "minishell.h"

void env_print(char **env)
{
    int i;

    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}
