#include "minishell.h"

void stract_variables(char *line, int *i)
{
    char *current_var;
    int end;
    int start;

    end = 0;
    start = (*i);
    while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"')
    {
        end++;
        (*i)++;
    }
    current_var = ft_substr(line, start, end);

    printf("VARIABLE = %s\n", current_var);
}

char **duplicate_envp(char **envp)
{
    int len;
    char **our_envp;

    len = 0;
    while (envp[len] != NULL)
        len++;
    
    our_envp = malloc(sizeof(char *) * (len + 1));

    len = 0;

    while (envp[len] != NULL)
    {
        our_envp[len] = ft_strdup(envp[len]);
        len++;
    }

    our_envp[len] = NULL;
    return our_envp;
}