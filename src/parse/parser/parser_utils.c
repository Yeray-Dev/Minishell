#include "minishell.h"

size_t count_tokes(t_list_token *s_list_token)
{
    size_t count;
    t_tokens *temp;

    temp = s_list_token->top;
    count = 0;
    while (temp != NULL && temp->type != TOKEN_PIPE 
            && temp->type != TOKEN_REDIRECTIONS)
    {
        count++;
        temp = temp->next;
    }
    return count;
}
void add_cmd_list(t_cmd *new_cmd, t_list_cmd *list_cmd)
{
    new_cmd->next = NULL;
    printf("Has pipe%d", new_cmd->has_pipe);
    if (list_cmd->top == NULL)
    {
        list_cmd->top = new_cmd;
        list_cmd->last = new_cmd;
    }
    else
    {
        list_cmd->last->next = new_cmd;
        list_cmd->last = new_cmd;
    }
}
void set_cmd_link_type(t_cmd *new_cmd, t_tokens **end_token)
{
    if (!end_token || !*end_token)
        return;
    if ((*end_token)->type == TOKEN_PIPE)
        new_cmd->has_pipe = 1;
    else if ((*end_token)->type == TOKEN_REDIRECTIONS)
    {
        if (ft_strncmp((*end_token)->name, "<", 1) == 0 && (*end_token)->next)
            new_cmd->infile = ft_strdup((*end_token)->next->name);
        else if (ft_strncmp((*end_token)->name, ">", 1) == 0 && (*end_token)->next)
            new_cmd->outfile = ft_strdup((*end_token)->next->name);
        else if (ft_strncmp((*end_token)->name, "<<", 2) == 0 && (*end_token)->next)
        {
            new_cmd->heredoc_word = ft_strdup((*end_token)->next->name);
            new_cmd->is_heredoc = 1;
        }
        else if (ft_strncmp((*end_token)->name, ">>", 2) == 0 && (*end_token)->next)
        {
            new_cmd->outfile = ft_strdup((*end_token)->next->name);
            new_cmd->append = 1;
        }
        *end_token = (*end_token)->next;
    }
}
void create_cmd(t_list_token *s_list_token, t_list_cmd *list_cmd)
{
    while(s_list_token->top != NULL) 
    {
        t_cmd *current_cmd;
        int i;

        current_cmd = malloc(sizeof(t_cmd));
        if (!current_cmd)
            return ;
        i = 0;
        current_cmd->argv = malloc(sizeof(char *) * (count_tokes(s_list_token) + 1));
        if(!current_cmd->argv)
            return ;    
        while (s_list_token->top != NULL 
                && s_list_token->top->type != TOKEN_PIPE 
                && s_list_token->top->type != TOKEN_REDIRECTIONS)
        {
            current_cmd->argv[i++] = ft_strdup(s_list_token->top->name);
            s_list_token->top = s_list_token->top->next;
        }
        current_cmd->argv[i] = NULL;
        complete_cmd(current_cmd, list_cmd, &s_list_token->top); // AQUI LLAMO A LA FUNCION QUE LUEGO LLAMARA A set_cmd_link_type
        if (s_list_token->top != NULL)
            s_list_token->top = s_list_token->top->next;
    }
}
  // //! TESTING
    // int lista = 0;
    // while (list_cmd->top != NULL)
    // {
    //     int j = 0;
    //     printf("CMD = %d",lista);
    //     while(list_cmd->top->argv[j] != NULL)
    //     {
    //         printf(" %s", list_cmd->top->argv[j]);
    //         j++;
    //     }
    //     printf("Posicion %d\n", list_cmd->top->position);
    //     lista++;
    //     list_cmd->top = list_cmd->top->next;
    // }
    // //! END TESTING
//. AQUI IRA LA FUNCION QUE GESTIONE LOS PIPE Y REDIRECCIONES
