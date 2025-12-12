#include "minishell.h"

int parser(char *line, t_list_token *list_token)
{
    if (line == NULL)
    {
        write(1, "\n", 1);
        exit(1);
    }
    else
    {
        add_history(line);
        init_token(line, list_token);
    }
    return 1;
}
