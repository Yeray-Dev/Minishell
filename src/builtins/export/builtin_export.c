#include "minishell.h"


static int export_print(t_shell *sh)
{
    char    **sorted;
    int     i;

    sorted = env_copy(sh->env);
    if (!sorted)
        return (1);
    env_sort(sorted);
    i = 0;
    while (sorted[i])
    {
        print_export(sorted[i]);
        free(sorted[i]);
        i++;
    }
    free(sorted);
    return (0);
}

static int export_args(t_shell *sh, t_cmd *cmd)
{
    int i;
    int has_error;

    i = 1;
    has_error = 0;
    while (cmd->args_name[i])
    {
        export_one(sh, cmd->args_name[i], &has_error);
        i++;
    }
    if (has_error)
        return (1);
    return (0);
}

int builtin_export(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name[1])
        sh->exit_status = export_print(sh);
    else
        sh->exit_status = export_args(sh, cmd);
    return (sh->exit_status);
}

