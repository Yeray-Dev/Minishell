#include "minishell.h"

void print_name_token(t_list_token *list_token){
    t_tokens *tmp = list_token->top;
    while(tmp != NULL)
    {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}
void print_typetoken(t_list_token *token){
    t_tokens *tmp2 = token->top;
    while(tmp2 != NULL)
    {
        printf("%d\n", tmp2->type);
        tmp2 = tmp2->next;
    }
}