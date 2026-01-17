#include "minishell.h"

static void echo_print_arg(t_shell *sh, char *arg)
{
    if (arg == NULL)
        return;
    if (strcmp(arg, "$?") == 0) //crear ft_strcmp
    {
        if (sh != NULL)
            printf("%d", sh->exit_status);
        else
            printf("0");
    }
    else
        printf("%s", arg);
}

static void echo_print_args(t_shell *sh, char **args)
{
    int i;

    if (args == NULL)
        return;

    i = 0;
    while (args[i] != NULL)
    {
        echo_print_arg(sh, args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
}

static int echo_process_flags(char ***args)
{
    int print_newline;

    print_newline = 1;
    if (args != NULL && *args != NULL && strcmp((*args)[0], "-n") == 0)
    {
        print_newline = 0;
        (*args)++;
    }
    return (print_newline);
}

int builtin_echo(t_shell *sh, t_cmd *cmd)
{
    int print_newline;
    char **args;

    if (sh == NULL)
        return (0);
    if (cmd == NULL)
    {
        sh->exit_status = 1;
        return (sh->exit_status);
    }
    args = cmd->args_name;
    print_newline = echo_process_flags(&args);
    echo_print_args(sh, args);
    if (print_newline)
        printf("\n");
    sh->exit_status = 0;
    return (sh->exit_status);
}
