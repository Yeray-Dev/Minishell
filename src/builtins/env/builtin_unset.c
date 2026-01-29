#include "minishell.h"

static void shift_env_vars(char **env, int pos)
{
    while (env[pos + 1])
    {
        env[pos] = env[pos + 1];
        pos++;
    }
    env[pos] = NULL;
}

static void unset_single_var(char *var_name, char **env)
{
    int j;
    int len;

    j = 0;
    len = ft_strlen(var_name);
    while (env[j])
    {
        if (!ft_strncmp(var_name, env[j], len) &&
            (env[j][len] == '=' || env[j][len] == '\0'))
        {
            free(env[j]);
            shift_env_vars(env, j);
            break;
        }
        j++;
    }
}

int builtin_unset(t_shell *sh, t_cmd *cmd)
{
    int i;

    if (!sh || !cmd || !cmd->args_name)
        return (sh->exit_status = 1);

    i = 0;
    while (cmd->args_name[i])
    {
        unset_single_var(cmd->args_name[i], sh->env);
        i++;
    }
    sh->exit_status = 0;
    return (sh->exit_status);
}
