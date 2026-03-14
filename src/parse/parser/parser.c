#include "minishell.h"

void complete_cmd(t_cmd *new_cmd, t_list_cmd *list_cmd, t_tokens **token)
{
    set_cmd_link_type(new_cmd, token);
    add_cmd_list(new_cmd, list_cmd);
}

int parser(char *line, t_shell *t_shell)
{
    t_shell->list_token.top = NULL;
    t_shell->list_token.last = NULL;
    t_shell->cmd_list.top = NULL;
    t_shell->cmd_list.last = NULL;
    if (line == NULL)
        return (0);
    else
    {
        add_history(line);
        init_token(line, &t_shell->list_token, t_shell->our_envp);
        create_cmd(&t_shell->list_token, &t_shell->cmd_list);
    }
    return 1;
}