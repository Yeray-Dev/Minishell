#include "minishell.h"

char **env_init(char **envp)
{
    int i = 0;
    char **new_env;

    while (envp[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new_env[i] = strdup(envp[i]);
        if (!new_env[i])
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}
