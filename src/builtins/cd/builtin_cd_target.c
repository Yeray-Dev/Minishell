#include "minishell.h"

/* Devuelve ruta destino según argumento */
char *get_target_path(t_shell *sh, char *arg)
{
    if (!arg)
        return get_home_cached(sh);
    if (!ft_strcmp(arg, "-"))
        return get_local_env("OLDPWD", sh->env);
    if (!ft_strcmp(arg, "~"))
        return get_home_cached(sh);
    if (!ft_strcmp(arg, ".."))
        return get_parent_from_pwd(sh);
    return ft_strdup(arg);
}

/* Cambia directorio, imprime path si cd - */
int change_directory(t_shell *sh, char *path, char *arg)
{
    if (chdir(path) < 0)
    {
        print_chdir_error(path, arg);
        return 0;
    }
    if (arg && !ft_strcmp(arg, "-"))
        printf("%s\n", path);
    return 1;
}

/* Actualiza variables PWD y OLDPWD */
void update_environment(t_shell *sh, char *oldpwd, char *pwd)
{
    char *tmp;
    if (oldpwd)
    {
        tmp = ft_strjoin("OLDPWD=", oldpwd);
        if (tmp)
            env_set(&sh->env, tmp);
    }
    if (pwd)
    {
        tmp = ft_strjoin("PWD=", pwd);
        if (tmp)
        {
            env_set(&sh->env, tmp);
            free(pwd);
        }
    }
}