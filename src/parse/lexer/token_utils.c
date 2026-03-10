#include "minishell.h"

int token_is_quote(char *line, int *i, char **our_envp, t_list_token *list_token)
{
    char quote_char;

    if (line[*i] == QUOTES || line[*i] == QUOTE)
    {
        quote_char = line[*i];
        (*i)++;

        while (line[*i] != quote_char && line[*i] != '\0')
        {
            if (quote_char == QUOTES && line[*i] == '$' && line[*i -1] != '/')
                stract_variables(line, i, our_envp, list_token);
            (*i)++;
        }
        if (line[*i] == '\0')
        {
            ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n", 2);
            return (-1);
        }
        (*i)++;
        return 1;
        // if (line[*i] == quote_char)
        //     (*i)++;
    }
    return 0;
}
int token_is_pipe(char *line, int *i, int *start, t_list_token *list_token)
{
    char *new_token;

    if (line[*i] == PIPE)
    {
        if (*i > *start)
        {
            new_token = ft_substr(line, *start, *i - *start);
            token_add_list(list_token, new_token);
            free(new_token);
        }
        (*i)++;
        *start = *i;
        new_token = ft_substr(line, *i - 1, 1);
        token_add_list(list_token, new_token);
        list_token->last->type = TOKEN_PIPE;
        free(new_token);
        return (1);
    }
    return (0);
}
void token_is_double_redirect(char *line, int *i, int *start, t_list_token *list_token)
{       
    char *new_token;

    if(*i > *start)
    {
        new_token = ft_substr(line, *start, *i - *start);
        token_add_list(list_token, new_token);
        free(new_token);
    }
    (*i) += 2;
    *start = *i;
    new_token = ft_substr(line, *i - 2, 2);
    token_add_list(list_token, new_token);
    list_token->last->type = TOKEN_REDIRECTIONS;
    free(new_token);
}
int token_is_redirect(char *line, int *i, int *start, t_list_token *list_token)
{
    char *new_token;

    if (ft_strncmp(&line[*i], "<<", 2) == 0 || ft_strncmp(&line[*i], ">>", 2) == 0)
    {
        token_is_double_redirect(line, i, start, list_token);
        return (1);
    }
    else if (line[*i] == '<' || line[*i] == '>')
    {
        
        if (*i > *start)
        {
            new_token = ft_substr(line, *start, *i - *start);
            token_add_list(list_token, new_token);
            free(new_token);
        }
        (*i)++;
        *start = *i;
        new_token = ft_substr(line, *i - 1, 1);
        token_add_list(list_token, new_token);
        list_token->last->type = TOKEN_REDIRECTIONS;
        free(new_token);
        return (1);
    }
    return (0);
}