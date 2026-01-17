#include "minishell.h"

static void unset_arg(t_shell *sh, const char *arg)
{
    int res;

    res = env_unset(&sh->env, arg);
    if (res != 0)
        sh->exit_status = 1;
}

int builtin_unset(t_shell *sh, t_cmd *cmd)
{
    int i;

    if (!sh || !sh->env || !cmd || !cmd->args_name)
    {
        if (sh)
        {
            sh->exit_status = 1;
            return (sh->exit_status);
        }
        return (1);
    }
    sh->exit_status = 0;
    i = 0;
    while (cmd->args_name[i])
    {
        unset_arg(sh, cmd->args_name[i]);
        i++;
    }
    return (sh->exit_status);
}
