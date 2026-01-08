#include "minishell.h"

void env_print(char **env)
{
    int i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}
