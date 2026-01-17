#include "minishell.h"

static int is_valid_identifier(const char *str)
{
    int i;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void export_arg(t_shell *sh, const char *arg)
{
    int res;

    if (!is_valid_identifier(arg))
    {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", arg);
        sh->exit_status = 1;
        return;
    }
    res = env_set(&sh->env, arg);
    if (res != 0)
        sh->exit_status = 1;
}

int builtin_export(t_shell *sh, t_cmd *cmd)
{
    int i;

    if (!sh || !cmd || !cmd->args_name)
    {
        if (sh)
        {
            sh->exit_status = 1;
            return (sh->exit_status);
        }
        return (1);
    }

    sh->exit_status = 0;
    i = 0;
    while (cmd->args_name[i])
    {
        export_arg(sh, cmd->args_name[i]);
        i++;
    }
    return (sh->exit_status);
}
