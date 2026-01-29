#include "minishell.h"

static char **env_copy(char **env)
{
    int     i;
    char    **copy;

    i = 0;
    while (env[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (env[i])
    {
        copy[i] = ft_strdup(env[i]);
        if (!copy[i])
        {
            while (i > 0)
                free(copy[--i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

static void env_sort(char **env)
{
    int i;
    char *tmp;

    i = 0;
    while (env[i + 1])
    {
        if (ft_strcmp(env[i], env[i + 1]) > 0)
        {
            tmp = env[i];
            env[i] = env[i + 1];
            env[i + 1] = tmp;
            i = 0;
        }
        else
            i++;
    }
}

static void print_export(char *var)
{
    int i = 0;

    if (!var || !ft_strcmp(var, "_="))
        return;
    printf("declare -x ");
    while (var[i] && var[i] != '=')
        printf("%c", var[i++]);
    if (var[i] == '=')
    {
        printf("=\"");
        i++;
        while (var[i])
            printf("%c", var[i++]);
        printf("\"");
    }
    printf("\n");
}