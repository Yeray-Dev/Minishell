#include "minishell.h"

/* Env sin argumentos */
static void env_handle_no_args(t_shell *sh)
{
    if (!sh || !sh->env)
        return;
    update_underscore(sh);
    env_print(sh->env);
    sh->exit_status = 0;
}

/* Ejecuta env con variables temporales */
static void env_handle_temp_vars(t_shell *sh, char **args, int start)
{
    char **env_copy_local = copy_env(sh->env);
    if (!env_copy_local)
    {
        sh->exit_status = 1;
        return;
    }
    if (apply_temp_vars(args, start, &env_copy_local) != 0)
    {
        free_dblptr(env_copy_local);
        sh->exit_status = 1;
        return;
    }
    fork_and_exec(&args[start], env_copy_local, &sh->exit_status);
    free_dblptr(env_copy_local);
}

/* Builtin env */
int builtin_env(t_shell *sh, t_cmd *cmd)
{
    int cmd_start = 1;

    if (!sh || !cmd || !cmd->args_name)
    {
        if (sh)
            sh->exit_status = 1;
        return 1;
    }
    while (cmd->args_name[cmd_start] &&
           is_var_assignment(cmd->args_name[cmd_start]))
        cmd_start++;
    if (!cmd->args_name[cmd_start])
    {
        env_handle_no_args(sh);
        return sh->exit_status;
    }
    env_handle_temp_vars(sh, cmd->args_name, cmd_start);
    return sh->exit_status;
}
