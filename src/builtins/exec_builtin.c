#include "minishell.h"

void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd_name)
        return;

    if (strcmp(cmd->cmd_name, "pwd") == 0) //crear ft_strcmp
        cmd->builtin_type = BI_PWD;
    else if (strcmp(cmd->cmd_name, "echo") == 0)
        cmd->builtin_type = BI_ECHO;
    else if (strcmp(cmd->cmd_name, "env") == 0)
        cmd->builtin_type = BI_ENV;
    else if (strcmp(cmd->cmd_name, "export") == 0)
        cmd->builtin_type = BI_EXPORT;
    else if (strcmp(cmd->cmd_name, "unset") == 0)
        cmd->builtin_type = BI_UNSET;
    else
        cmd->builtin_type = BI_NONE;
}

int exec_builtin(t_cmd *cmd)
{
    int status;

    if (!cmd)
    {
        g_exit_status = 1;
        return (1);
    }
    if (cmd->builtin_type == BI_PWD)
        status = builtin_pwd(cmd);
    else if (cmd->builtin_type == BI_ECHO)
        status = builtin_echo(cmd);
    else if (cmd->builtin_type == BI_ENV)
        status = builtin_env(cmd);
    else if (cmd->builtin_type == BI_EXPORT)
        status = builtin_export(cmd);
    else if (cmd->builtin_type == BI_UNSET)
        status = builtin_unset(cmd);;
    else
        status = 1;
    g_exit_status = status;
    return (status);
}
