#include "minishell.h"

/* Exporta una sola variable */
void export_one(t_shell *sh, char *arg, int *has_error)
{
    char *name;
    int idx;

    if (!is_valid_identifier(arg))
    {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", arg);
        *has_error = 1;
        return;
    }
    name = get_var_name(arg);
    idx = env_get(sh->env, name);
    if (ft_strchr(arg, '='))
    {
        if (env_set(&sh->env, arg) != 0)
            *has_error = 1;
    }
    else if (idx == -1)
    {
        if (env_add_empty(&sh->env, name) != 0)
            *has_error = 1;
    }
    free(name);
}

/* Export sin argumentos: imprime todas las variables ordenadas */
int export_print(t_shell *sh)
{
    char **sorted = env_copy(sh->env);
    int i = 0;
    if (!sorted)
        return 1;
    env_sort(sorted);
    while (sorted[i])
    {
        print_export(sorted[i]);
        free(sorted[i]);
        i++;
    }
    free(sorted);
    return 0;
}

/* Export con argumentos: procesa cada variable */
int export_args(t_shell *sh, t_cmd *cmd)
{
    int i = 1;
    int has_error = 0;
    while (cmd->args_name[i])
    {
        export_one(sh, cmd->args_name[i], &has_error);
        i++;
    }
    return has_error ? 1 : 0;
}

/* Función principal del builtin export */
int builtin_export(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name[1])
        sh->exit_status = export_print(sh);
    else
        sh->exit_status = export_args(sh, cmd);
    return sh->exit_status;
}