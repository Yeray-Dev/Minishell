#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum e_builtin_type
{
    BI_NONE,
    BI_ECHO,
    BI_PWD
} t_builtin_type;

typedef struct s_cmd
{
    char *cmd_name;
    char *args_name;
    char *flag_name;
    char *path;
    int is_att;
    t_builtin_type builtin_type;
} t_cmd;


int g_exit_status = 0;

void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd_name)
        return;

    if (strcmp(cmd->cmd_name, "pwd") == 0)
        cmd->builtin_type = BI_PWD;
    else if (strcmp(cmd->cmd_name, "echo") == 0)
        cmd->builtin_type = BI_ECHO;
    else
        cmd->builtin_type = BI_NONE;
}

int builtin_echo(t_cmd *cmd)
{
    if (!cmd || !cmd->args_name)
    {
        printf("\n");
        return (0);
    }
    if (strcmp(cmd->args_name, "$?") == 0)
        printf("%d\n", g_exit_status);
    else
        printf("%s\n", cmd->args_name);
    return (0);
}

int builtin_pwd(t_cmd *cmd)
{
    char *cwd;
    (void)cmd;

    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
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
    else
        status = 1;
    g_exit_status = status;
    return (status);
}

/*int main(void)
{
    t_cmd cmd;

    cmd.cmd_name = "pwd";
    cmd.args_name = NULL;
    cmd.flag_name = NULL;
    cmd.path = NULL;
    cmd.is_att = 0;

    detect_builtin(&cmd);

    exec_builtin(&cmd);
    return (0);
}*/


int main(void)
{
    t_cmd cmd;

    /* ---- Simula: pwd ---- */
    cmd.cmd_name = "pwd";
    cmd.args_name = NULL;
    cmd.flag_name = NULL;
    cmd.path = NULL;
    cmd.is_att = 0;

    detect_builtin(&cmd);
    exec_builtin(&cmd);

    /* ---- Simula: echo $? ---- */
    cmd.cmd_name = "echo";
    cmd.args_name = "$?";
    detect_builtin(&cmd);
    exec_builtin(&cmd);

    return (0);
}
