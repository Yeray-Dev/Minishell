#include "minishell.h"

static char *get_var_name(const char *arg)
{
    int i = 0;

    while (arg[i] && arg[i] != '=')
        i++;
    return (ft_substr(arg, 0, i));
}

static int is_valid_identifier(const char *str)
{
    int i;

    if (!str || !str[0] || str[0] == '=')
        return (0);
    if (!ft_isalpha(str[0]) && str[0] != '_')
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

void export_one(t_shell *sh, char *arg, int *has_error)
{
    char *name;
    int idx;

    if (!is_valid_identifier(arg))
    {
        fprintf(stderr,
            "minishell: export: `%s': not a valid identifier\n", arg);
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
