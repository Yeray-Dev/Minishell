#include "minishell.h"

/* Desplaza variables en env tras unset */
static void shift_env_vars(char **env, int pos)
{
    while (env[pos + 1])
    {
        env[pos] = env[pos + 1];
        pos++;
    }
    env[pos] = NULL;
}

/* Elimina una variable */
static void unset_single_var(char *var_name, char **env)
{
    int j = 0;
    int len = ft_strlen(var_name);

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

/* Builtin unset */
int builtin_unset(t_shell *sh, t_cmd *cmd)
{
    int i = 0;
    if (!sh || !cmd || !cmd->args_name)
        return sh->exit_status = 1;

    while (cmd->args_name[i])
    {
        unset_single_var(cmd->args_name[i], sh->env);
        i++;
    }
    sh->exit_status = 0;
    return sh->exit_status;
}