/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:42:15 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 15:42:15 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_local_env(const char *key, char **env)
{
	int	idx;

	if (!key || !env)
		return (NULL);
	idx = env_get(env, key);
	if (idx == -1)
		return (NULL);
	return (env[idx] + ft_strlen(key) + 1);
}

char	*get_var_value(const char *key, t_shell *sh)
{
	return (get_local_env(key, sh->our_envp));
}

char	*get_home_cached(t_shell *sh)
{
	char	*home;

	home = get_var_value("HOME", sh);
	if (!home || home[0] == '\0')
		return (sh->cd_home);
	if (!sh->cd_home || ft_strcmp(sh->cd_home, home) != 0)
	{
		free(sh->cd_home);
		sh->cd_home = ft_strdup(home);
		if (!sh->cd_home)
		{
			ft_putstr_fd("minishell: cd: malloc failed\n", 2);
			sh->exit_status = 1;
			return (NULL);
		}
	}
	return (sh->cd_home);
}

int	needs_free(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "-") == 0 || ft_strcmp(arg, "~") == 0)
		return (0);
	return (1);
}

void	print_chdir_error(char *path, char *arg)
{
	(void)path;
	if (arg != NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
	}
	else
		ft_putstr_fd("minishell: cd: HOME", 2);
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}
