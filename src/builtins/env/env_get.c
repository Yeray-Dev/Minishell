#include "minishell.h"

int env_get(char **env, const char *key)
{
    int     i;
    size_t  key_len;

    if (!env || !key)
        return (-1);
    i = 0;
    key_len = ft_strlen(key);
    while (env[i])
    {
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}
