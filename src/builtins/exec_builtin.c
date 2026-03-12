#include "minishell.h"

void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;

    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        cmd->builtin_type = BI_PWD;
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        cmd->builtin_type = BI_ECHO;
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        cmd->builtin_type = BI_ENV;
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        cmd->builtin_type = BI_EXPORT;
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        cmd->builtin_type = BI_UNSET;
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        cmd->builtin_type = BI_CD;
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        cmd->builtin_type = BI_EXIT;
    else
        cmd->builtin_type = BI_NONE;
}

int exec_builtin(t_shell *sh, t_cmd *cmd) //crear sh en el main
{
    int status;

    if (!cmd || !sh)
        return (1);
    detect_builtin(cmd);
    status = 0;
    if (cmd->builtin_type == BI_PWD)
        status = builtin_pwd(sh, cmd);
    else if (cmd->builtin_type == BI_ECHO)
        status = builtin_echo(sh, cmd);
    else if (cmd->builtin_type == BI_ENV)
        status = builtin_env(sh, cmd);
    else if (cmd->builtin_type == BI_EXPORT)
        status = builtin_export(sh, cmd);
    else if (cmd->builtin_type == BI_UNSET)
        status = builtin_unset(sh, cmd);
    else if (cmd->builtin_type == BI_CD)
        status = builtin_cd(sh, cmd);
    else if (cmd->builtin_type == BI_EXIT)
    {
        builtin_exit(sh, cmd);
        return (sh->last_status);
    }
    else
        status = 1;
    sh->last_status = status;
    return (status);
}
