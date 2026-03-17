/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_target.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:44:35 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 15:44:35 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_target_path(t_shell *sh, char *arg)
{
	if (!arg)
		return (get_home_cached(sh));
	if (!ft_strcmp(arg, "-"))
		return (get_local_env("OLDPWD", sh->our_envp));
	if (!ft_strcmp(arg, "~"))
		return (get_home_cached(sh));
	if (!ft_strcmp(arg, ".."))
		return (get_parent_from_pwd(sh));
	return (ft_strdup(arg));
}

int	change_directory(t_shell *sh, char *path, char *arg)
{
	(void)sh;
	if (chdir(path) < 0)
	{
		print_chdir_error(path, arg);
		return (0);
	}
	if (arg && !ft_strcmp(arg, "-"))
		printf("%s\n", path);
	return (1);
}

void	update_environment(t_shell *sh, char *oldpwd, char *pwd)
{
	char	*tmp;

	if (oldpwd)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		if (tmp)
		{
			env_set(&sh->our_envp, tmp);
			free(tmp);
		}
	}
	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd);
		if (tmp)
		{
			env_set(&sh->our_envp, tmp);
			free(tmp);
		}
		free(pwd);
	}
}
