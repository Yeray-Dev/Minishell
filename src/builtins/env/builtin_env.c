#include "minishell.h"

int builtin_env(t_shell *sh, t_cmd *cmd)
{
    (void)cmd;
    env_print(sh->env);
    return (0);
}
