#include "minishell.h"

/* Duplicar entorno */
char **copy_env(char **env)
{
    int i = 0;
    char **new_env;

    while (env && env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return NULL;
    i = 0;
    while (env && env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return NULL;
        }
        i++;
    }
    new_env[i] = NULL;
    return new_env;
}

/* Inicializar entorno al inicio del shell */
char **env_init(char **envp)
{
    return copy_env(envp);
}

/* Aplica variables temporales antes de ejecutar comando */
int apply_temp_vars(char **tokens, int end, char ***envp)
{
    int i;
    int res;

    i = 1;
    while (i < end)
    {
        res = env_set(envp, tokens[i]);
        if (res != 0)
            return res;
        i++;
    }
    return 0;
}