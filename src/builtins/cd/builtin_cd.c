#include "minishell.h"

/* Comprueba si hay demasiados argumentos */
static int check_multiple_args(t_cmd *cmd, t_shell *sh)
{
    if (cmd->args_name[1] && cmd->args_name[2])
    {
        fprintf(stderr, "minishell: cd: too many arguments\n");
        sh->exit_status = 2;
        return 1;
    }
    return 0;
}

/* Función principal del builtin cd */
void builtin_cd(t_shell *sh, t_cmd *cmd)
{
    char *arg;
    char *path;
    char *oldpwd;
    char *pwd;

    if (check_multiple_args(cmd, sh))
        return;
    arg = cmd->args_name[1];
    path = get_target_path(sh, arg);
    if (!path)
        return;
    oldpwd = get_local_env("PWD", sh->env);
    if (!change_directory(sh, path, arg))
        return;
    pwd = get_new_pwd(oldpwd, path, arg);
    if (needs_free(arg))
        free(path);
    update_environment(sh, oldpwd, pwd);
    sh->exit_status = 0;
}