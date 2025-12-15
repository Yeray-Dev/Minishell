#include "minishell.h"

static void token_stract_tokens(char *line, t_list_token *list_token)
{
    int i;
    int start;
    char *new_token;

    i = 0;
    while (line[i] == ' ')
        i++;
    while(line[i] != '\0')
    {
        start = i;
        while (line[i] != ' ' && line[i] != '\0')
        {
            if (token_is_quote(line, &i))
                break;
            if (token_is_pipe(line, &i, &start, list_token) || token_is_redirect(line, &i, &start, list_token))
            {
                while (line[i] == ' ')
                    i++;
                start = i;
                continue;
            }
            if (line[i] != '\0')
                i++;
        }
        i++;
        if (i - start > 0)
        {
            new_token = ft_substr(line, start, i - start);
            token_add_list(list_token, new_token);
            free(new_token);
        }
    }
}


void token_add_list(t_list_token *list_token, char* new_token)
{
        t_tokens *token;

        if (!list_token || !new_token)
            return;
        token = malloc(sizeof(t_tokens));
        if (!token)
            return;
        token->name = ft_strdup(new_token);
        token->next = NULL;
        if (list_token->top == NULL)
        {
            list_token->top = token;
            list_token->last = token;
        }
        else
        {
            list_token->last->next = token;
            list_token->last = token;
        }
}
//! TESTING
static void ft_token_type(t_list_token *token)
{
    t_tokens *tmp;

    tmp = token->top;
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->name, "|", 1) == 0)
        {
            tmp->type = TOKEN_PIPE;
            printf("AQUI");
        }
        else if (ft_strncmp(tmp->name, "<", 1) == 0 || 
                ft_strncmp(tmp->name, "<<", 2) == 0 ||
                ft_strncmp(tmp->name, ">", 1) == 0 ||
                ft_strncmp(tmp->name, ">>", 2) == 0)
            tmp->type = TOKEN_REDIRECTIONS;
        else
            tmp->type = TOKEN_CMD;
        tmp = tmp->next;
    }
}
//! END TESTING

int init_token(char *line, t_list_token *list_token)
{
    if (line != NULL)
    {
        token_stract_tokens(line, list_token);
        ft_token_type(list_token);
    }
    t_tokens *current = list_token->top;

    while(current != NULL)
    {
        printf("CMD = %s, TYPE = %d\n", current->name, current->type); //! TESTING
        current = current->next;
    }
    return 1;
}