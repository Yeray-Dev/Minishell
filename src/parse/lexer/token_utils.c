#include "minishell.h"

int token_is_quote(char *line, int *i)
{
    char q;

    if (line[*i] == QUOTES || line[*i] == QUOTE)
    {
        q = line[*i];
        (*i)++;

        while (line[*i] != q && line[*i] != '\0')
            (*i)++;
        if (line[*i] == q)
            (*i)++;
        return 1;
    }
    return 0;
}
int token_is_pipe(char *line, int *i, int *start, t_list_token *list_token)
{
    char *new_token;

    if (line[*i] == PIPE)
    {
        if (*i > 0 && line[*i - 1] != ' ')
        {
            new_token = ft_substr(line, *start, *i - *start);
            token_add_list(list_token, new_token);
            free(new_token);
        }
        (*i)++;
        *start = *i;
        new_token = ft_substr(line, *i - 1, 1);
        token_add_list(list_token, new_token);
        free(new_token);
        return (1);
    }
    return (0);
}
void token_is_double_redirect(char *line, int *i, int *start, t_list_token *list_token)
{       
    char *new_token;

    if (*i > 0 && line[*i - 1] != ' ')
    {
        new_token = ft_substr(line, *start, *i - *start);
        token_add_list(list_token, new_token);
        free(new_token);
    }
    (*i) += 2;
    *start = *i;
    new_token = ft_substr(line, *i - 2, 2);
    token_add_list(list_token, new_token);
    free(new_token);
}
int token_is_redirect(char *line, int *i, int *start, t_list_token *list_token)
{
    char *new_token;

    if (ft_strncmp(&line[*i], "<<", 2) == 0 || ft_strncmp(&line[*i], ">>", 2) == 0)
        token_is_double_redirect(line, i, start, list_token);
    else if (line[*i] == '<' || line[*i] == '>')
    {
        if (*i > 0 && line[*i - 1] != ' ')
        {
            new_token = ft_substr(line, *start, *i - *start);
            token_add_list(list_token, new_token);
           printf("PRIMERO: %s\n", new_token); //! TESTING
            free(new_token);
        }
        (*i)++;
        *start = *i;
        new_token = ft_substr(line, *i - 1, 1);
        token_add_list(list_token, new_token);
        printf("TERCERO: %s\n", new_token); //! TESTING
        free(new_token);
        return (1);
    }
    return 0;
}
