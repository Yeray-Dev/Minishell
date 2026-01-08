#include "minishell.h"

static int count_env(char **env)
{
    int i = 0;

    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

static int copy_env_skip(char ***env, int idx)
{
    int     i = 0;
    int     j = 0;
    int     size;
    char    **new_env;

    size = count_env(*env);
    new_env = malloc(sizeof(char *) * size);
    if (!new_env)
        return (-1);
    while ((*env)[i])
    {
        if (i != idx)
        {
            new_env[j] = (*env)[i];
            j++;
        }
        else
            free((*env)[i]);
        i++;
    }
    new_env[j] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int env_unset(char ***env, const char *key)
{
    int idx;

    if (!env || !key)
        return (-1);
    idx = env_get(*env, key);
    if (idx == -1)
        return (0);
    return copy_env_skip(env, idx);
}
