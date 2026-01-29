#include "minishell.h"

char *get_target_path(t_shell *sh, char *arg)
{
    char *home;

    if (!arg)
        return handle_home_dir(sh);
    if (!ft_strcmp(arg, "-"))
        return handle_oldpwd_dir(sh);
    if (!ft_strcmp(arg, "~"))
        return get_home_cached(sh);
    if (!ft_strcmp(arg, ".."))
        return get_parent_from_pwd(sh);
    return ft_strdup(arg);
}

int change_directory(t_shell *sh, char *path, char *arg)
{
    if (chdir(path) < 0)
    {
        print_chdir_error(path, arg);
        return 0;
    }
    if (arg && !ft_strcmp(arg, "-"))
    {
        write(STDOUT_FILENO, path, ft_strlen(path));
        write(STDOUT_FILENO, "\n", 1);
    }
    return 1;
}

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
            env_set(&sh->env, tmp);
        free(pwd);
    }
}
