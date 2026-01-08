#include "minishell.h"

int builtin_export(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name)
        return (0);
    if (env_set(&sh->env, cmd->args_name) != 0)
    {
        perror("export");
        return (1);
    }
    return (0);
}
