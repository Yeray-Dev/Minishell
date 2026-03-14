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
void free_cmd_list(t_list_cmd *list_cmd)
{
    t_cmd *cmd;
    t_cmd *next;

    cmd = list_cmd->top;
    while(cmd)
    {
        next = cmd->next;
        int i = 0;
        while (cmd->argv[i])
            free(cmd->argv[i++]);
        free(cmd->argv);
        if (cmd->infile) 
         free(cmd->infile);
        if (cmd->outfile)     
         free(cmd->outfile);
        if (cmd->heredoc_word) 
         free(cmd->heredoc_word);
        if (cmd->heredoc_fd != -1)
             close(cmd->heredoc_fd);
        free(cmd);
        cmd = next; 
    }
    list_cmd->top = NULL;
    list_cmd->last = NULL;
}

void add_cmd_list(t_cmd *new_cmd, t_list_cmd *list_cmd)
{
    new_cmd->next = NULL;
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

        if (ft_strncmp((*end_token)->name, "<<", 2) == 0 && (*end_token)->next)
        {
            new_cmd->heredoc_word = ft_strdup((*end_token)->next->name);
            new_cmd->is_heredoc = 1;
        }
        else if (ft_strncmp((*end_token)->name, ">>", 2) == 0 && (*end_token)->next)
        {
            new_cmd->outfile = ft_strdup((*end_token)->next->name);
            new_cmd->append = 1;
        }
        else if (ft_strncmp((*end_token)->name, "<", 1) == 0 && (*end_token)->next)
            new_cmd->infile = ft_strdup((*end_token)->next->name);
        else if (ft_strncmp((*end_token)->name, ">", 1) == 0 && (*end_token)->next)
            new_cmd->outfile = ft_strdup((*end_token)->next->name);
        *end_token = (*end_token)->next;
    }
}
void create_cmd(t_list_token *s_list_token, t_list_cmd *list_cmd)
{
    while(s_list_token->top != NULL) 
    {
        t_cmd *current_cmd;
        int i;

        current_cmd = ft_calloc(1, sizeof(t_cmd));
        if (!current_cmd)
            return ;
        current_cmd->heredoc_fd = -1;
        i = 0;
        current_cmd->argv = malloc(sizeof(char *) * (count_tokes(s_list_token) + 1));
        if(!current_cmd->argv)
        {
            free(current_cmd);
            return ;    
        }
        while (s_list_token->top != NULL 
                && s_list_token->top->type != TOKEN_PIPE 
                && s_list_token->top->type != TOKEN_REDIRECTIONS)
        {
            current_cmd->argv[i++] = ft_strdup(s_list_token->top->name);
            s_list_token->top = s_list_token->top->next;
        }
        current_cmd->argv[i] = NULL;
        while (s_list_token->top != NULL
                && s_list_token->top->type != TOKEN_CMD)
        {
            set_cmd_link_type(current_cmd, &s_list_token->top);
            if (s_list_token->top != NULL)
                s_list_token->top = s_list_token->top->next;
        }
        
        detect_builtin(current_cmd);
        add_cmd_list(current_cmd, list_cmd);
    }
}
