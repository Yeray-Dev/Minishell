#include "minishell.h"

int builtin_env(t_shell *sh, t_cmd *cmd)
{
    (void)cmd;

    if (!sh || !sh->env)
    {
        if (sh)
        {
            sh->exit_status = 1;
            return (sh->exit_status);
        }
        return (1);
    }
    env_print(sh->env);
    sh->exit_status = 0;
    return (sh->exit_status);
}
