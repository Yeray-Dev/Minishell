#include "minishell.h"
#include <stdlib.h>

static int count_env(char **env)
{
    int i;

    if (!env)
        return (0);
    i = 0;
    while (env[i])
        i++;
    return (i);
}

static char **env_create_new(char **env, int idx)
{
    char    **new_env;
    int     size;
    int     i;

    size = count_env(env);
    new_env = malloc(sizeof(char *) * size);
    if (!new_env)
        return (NULL);
    i = 0;
    while (i < idx)
    {
        new_env[i] = env[i];
        i++;
    }
    free(env[idx]);
    return (new_env);
}

static void env_copy_rest(char **old_env, char **new_env, int idx)
{
    int i;
    int j;

    i = idx + 1;
    j = idx;
    while (old_env[i])
    {
        new_env[j] = old_env[i];
        i++;
        j++;
    }
    new_env[j] = NULL;
    free(old_env);
}

int env_unset(char ***env, const char *key)
{
    int     idx;
    char    **new_env;

    if (!env || !key)
        return (-1);
    idx = env_get(*env, key);
    if (idx == -1)
        return (0);
    new_env = env_create_new(*env, idx);
    if (!new_env)
        return (-1);
    env_copy_rest(*env, new_env, idx);
    *env = new_env;
    return (0);
}
