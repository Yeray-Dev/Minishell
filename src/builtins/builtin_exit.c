#include "minishell.h"

static void handle_exit_invalid_arg(t_shell *sh, char *arg)
{
    write(STDERR_FILENO, "minishell: exit: ", 17);
    write(STDERR_FILENO, arg, ft_strlen(arg));
    write(STDERR_FILENO, ": numeric argument required\n", 28);
    sh->exit_status = 2;
}

static void handle_exit_too_many_args(t_shell *sh)
{
    write(STDERR_FILENO, "minishell: exit: too many arguments\n", 35);
    sh->exit_status = 2;
}

void builtin_exit(t_shell *sh, t_cmd *cmd)
{
    long long exit_code = 0;
    bool invalid = false;

    write(STDOUT_FILENO, "exit\n", 5);
    sh->exit_status = 0;

    if (cmd->args_name[1])
    {
        exit_code = atoi_overflow(cmd->args_name[1], &invalid);
        if (invalid)
        {
            handle_exit_invalid_arg(sh, cmd->args_name[1]);
            return;
        }
    }
    if (cmd->args_name[1] && cmd->args_name[2])
    {
        handle_exit_too_many_args(sh);
        return;
    }
    // Aquí habría que liberar memoria de la shell antes de salir
    if (!cmd->args_name[1])
        exit((int)sh->exit_status);
    else
        exit((int)(exit_code % 256));
}
