#include "minishell.h"

/* Devuelve 1 si arg es un -n válido (como -n, -nn, -nnn), 0 en caso contrario */
static int is_n_flag(char *arg)
{
    int i;

    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return 0;
    i = 2;
    while (arg[i] == 'n')
        i++;
    return arg[i] == '\0';
}

int builtin_echo(t_shell *sh, t_cmd *cmd)
{
    int i = 1;
    int print_newline = 1;

    /* Detectar flags -n iniciales */
    while (cmd->args_name[i] && is_n_flag(cmd->args_name[i]))
    {
        print_newline = 0;
        i++;
    }

    /* Imprimir argumentos restantes */
    while (cmd->args_name[i])
    {
        if (cmd->args_name[i][0] == '$' && cmd->args_name[i][1] == '?' && cmd->args_name[i][2] == '\0')
            printf("%d", sh->exit_status);  // Caso echo $?
        else
            printf("%s", cmd->args_name[i]);

        if (cmd->args_name[i + 1])
            printf(" ");
        i++;
    }

    if (print_newline)
        printf("\n");

    sh->exit_status = 0;
    return sh->exit_status;
}