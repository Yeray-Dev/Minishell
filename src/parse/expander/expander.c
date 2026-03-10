#include "minishell.h"
int expander_variable(char *current_var, char **our_envp, t_list_token *list_token)
{
    int i;
    size_t len;
    size_t len_envp;
    char *new_token;

    i = 0;
    len = ft_strlen(current_var);
    while (our_envp[i])
    {
        if (len < ft_strlen(our_envp[i]) && our_envp[i][len] == '=')
        {
            if (ft_strncmp(our_envp[i], current_var, len)  == 0)
            {
                len_envp = ft_strlen(our_envp[i]);
                new_token = ft_substr(our_envp[i], len + 1, (len_envp - len - 1));
                token_add_list(list_token, new_token);
                free(new_token);
                list_token->last->type = TOKEN_CMD;
                break;
            }
        }
        i++;
    }
    return 0;
}

int stract_variables(char *line, int *i, char **our_envp, t_list_token *list_token)
{
    char *current_var;
    int end;
    int start;

    start = (*i) + 1;
    end = start;
    while (line[end] && line[end] != ' ' && line[end] != '$'
            && line[end] != '"' && line[end] != '\'' && line[end] != '/'
            && line[end] != '|'  && line[end] != '<'  && line[end] != '>' && line[end] != '=')
        end++;
    current_var = ft_substr(line, start, end - start);
    expander_variable(current_var, our_envp, list_token);
    free(current_var);
    return (end - (*i));
}
char **duplicate_envp(char **envp)
{
    int len;
    char **our_envp;

    len = 0;
    while (envp[len] != NULL)
        len++;
    
    our_envp = malloc(sizeof(char *) * (len + 1));
    if (!our_envp)
        return NULL;
    len = 0;
    while (envp[len] != NULL)
    {
        our_envp[len] = ft_strdup(envp[len]);
        len++;
    }
    our_envp[len] = NULL;
    return our_envp;
}