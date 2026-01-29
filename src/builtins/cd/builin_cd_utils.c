#include "minishell.h"

char	*get_home_cached(t_shell *sh)
{
	char	*home;

	home = get_var_value("HOME", sh);
	if (home && home[0] != '\0')
	{
		if (!sh->cd_home || ft_strcmp(home, sh->cd_home) != 0)
		{
			if (sh->cd_home)
				free(sh->cd_home);
			sh->cd_home = ft_strdup(home);
			if (!sh->cd_home)
			{
				write(2, "minishell: cd: malloc failed\n", 29);
				sh->exit_status = 1;
				return (NULL);
			}
		}
		return (sh->cd_home);
	}
	if (sh->cd_home)
		return (sh->cd_home);
	return (NULL);
}

char	*handle_home_dir(t_shell *sh)
{
	char	*home;

	home = get_var_value("HOME", sh);
	return (update_home_cache(sh, home));
}

char	*handle_oldpwd_dir(t_shell *sh)
{
	char	*oldpwd;

	oldpwd = get_local_env("OLDPWD", sh->env);
	if (!oldpwd)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		sh->exit_status = 1;
		return (NULL);
	}
	return (oldpwd);
}

char	*update_home_cache(t_shell *sh, char *current)
{
	if (current && current[0] != '\0')
	{
		if (!sh->cd_home || ft_strcmp(current, sh->cd_home) != 0)
		{
			if (sh->cd_home)
				free(sh->cd_home);
			sh->cd_home = ft_strdup(current);
			if (!sh->cd_home)
			{
				write(2, "minishell: cd: malloc failed\n", 29);
				sh->exit_status = 1;
				return (NULL);
			}
		}
		return (sh->cd_home);
	}
	if (sh->cd_home)
		return (sh->cd_home);
	write(2, "minishell: cd: HOME not set\n", 28);
	sh->exit_status = 1;
	return (NULL);
}

void	print_chdir_error(char *path, char *arg)
{
	write(2, "minishell: cd: ", 15);
	if (arg && !ft_strcmp(arg, "-"))
		write(2, path, ft_strlen(path));
	else if (arg && !ft_strcmp(arg, "~"))
		write(2, path, ft_strlen(path));
	else if (arg)
		write(2, arg, ft_strlen(arg));
	else
		write(2, "HOME", 4);

	if (errno == EACCES)
		write(2, ": Permission denied\n", 20);
	else if (errno == ENOTDIR)
		write(2, ": Not a directory\n", 18);
	else
		write(2, ": No such file or directory\n", 28);
}
