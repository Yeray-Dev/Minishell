#include "minishell.h"

int builtin_unset(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name)
        return (0);
    if (env_unset(&sh->env, cmd->args_name) != 0)
    {
        perror("unset");
        return (1);
    }
    return (0);
}
