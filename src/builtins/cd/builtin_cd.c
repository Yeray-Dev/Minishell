/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:40:26 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:40:26 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_multiple_args(t_cmd *cmd, t_shell *sh)
{
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		sh->last_status = 1;
		return (1);
	}
	return (0);
}

static char	*resolve_cd_path(t_shell *sh, t_cmd *cmd)
{
	char	*path;

	if (!cmd->argv[1])
	{
		path = get_local_env("HOME", sh->our_envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (!ft_strcmp(cmd->argv[1], "~"))
		path = get_home_cached(sh);
	else if (!ft_strcmp(cmd->argv[1], "-"))
	{
		path = get_local_env("OLDPWD", sh->our_envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
	}
	else
		path = cmd->argv[1];
	return (path);
}

int	builtin_cd(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (check_multiple_args(cmd, sh))
		return (1);
	path = resolve_cd_path(sh, cmd);
	if (!path)
		return (1);
	oldpwd = get_local_env("PWD", sh->our_envp);
	if (cmd->argv[1] && !ft_strcmp(cmd->argv[1], "-"))
		printf("%s\n", path);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		sh->last_status = 1;
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_environment(sh, oldpwd, newpwd);
	sh->last_status = 0;
	return (0);
}
