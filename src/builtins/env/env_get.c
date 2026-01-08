#include "minishell.h"

int env_get(char **env, const char *key)
{
    int i = 0;
    size_t key_len = strlen(key);

    while (env && env[i])
    {
        if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}
