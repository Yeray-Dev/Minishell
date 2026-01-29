#include "minishell.h"

char *get_local_env(const char *key, char **env)
{
    int idx;

    if (!key || !env)
        return NULL;
    idx = env_get(env, key);
    if (idx == -1)
        return NULL;
    return env[idx] + ft_strlen(key) + 1;
}

char *get_var_value(const char *key, t_shell *sh)
{
    return get_local_env(key, sh->env);
}

int needs_free(char *arg)
{
    if (!arg)
        return 0;
    if (ft_strcmp(arg, "-") == 0 || ft_strcmp(arg, "~") == 0)
        return 0; /* estos punteros apuntan al cache o variables existentes */
    return 1; /* cualquier otro string duplicado debe liberarse */
}