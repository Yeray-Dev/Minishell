#include "minishell.h"

int builtin_echo(t_cmd *cmd)
{
    if (!cmd || !cmd->args_name)
    {
        printf("\n");
        return (0);
    }
    if (strcmp(cmd->args_name, "$?") == 0)
        printf("%d\n", g_exit_status);
    else
        printf("%s\n", cmd->args_name);
    return (0);
}
