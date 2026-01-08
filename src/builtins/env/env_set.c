#include "minishell.h"

static int env_replace(char **env, int idx, const char *var)
{
    char *new_var;

    new_var = strdup(var);
    if (!new_var)
        return (-1);
    free(env[idx]);
    env[idx] = new_var;
    return (0);
}

static int env_add(char ***env, const char *var)
{
    char    **new_env;
    int     i;

    i = 0;
    while (*env && (*env)[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (-1);
    i = 0;
    while (*env && (*env)[i])
    {
        new_env[i] = (*env)[i];
        i++;
    }
    new_env[i] = strdup(var);
    if (!new_env[i])
    {
        free(new_env);
        return (-1);
    }
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int env_set(char ***env, const char *var)
{
    int idx;

    if (!env || !var)
        return (-1);
    idx = env_get(*env, var);
    if (idx != -1)
        return env_replace(*env, idx, var);
    return env_add(env, var);
}
