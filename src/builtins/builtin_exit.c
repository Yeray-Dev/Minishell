#include "minishell.h"

static void handle_exit_invalid_arg(t_shell *sh, char *arg)
{
    printf("minishell: exit: %s: numeric argument required\n", arg);
    sh->exit_status = 2;
}

static void handle_exit_too_many_args(t_shell *sh)
{
    printf("minishell: exit: too many arguments\n");
    sh->exit_status = 2;
}

void builtin_exit(t_shell *sh, t_cmd *cmd)
{
    long long exit_code = 0;
    bool invalid = false;

    printf("exit\n");
    sh->exit_status = 0;

    /* Si hay argumento, intentar convertir a número */
    if (cmd->args_name[1])
    {
        exit_code = atoi_overflow(cmd->args_name[1], &invalid);
        if (invalid)
        {
            handle_exit_invalid_arg(sh, cmd->args_name[1]);
            return;  // No salimos del proceso si el argumento es inválido
        }
    }

    /* Si hay más de un argumento, error por demasiados argumentos */
    if (cmd->args_name[1] && cmd->args_name[2])
    {
        handle_exit_too_many_args(sh);
        return;
    }

    /* Aquí podrías liberar memoria de la shell si es necesario */

    if (!cmd->args_name[1])
        exit((int)sh->exit_status);
    else
        exit((int)(exit_code % 256));
}