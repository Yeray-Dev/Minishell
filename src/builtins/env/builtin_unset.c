/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:39:51 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:39:51 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_env_vars(char **env, int pos)
{
	while (env[pos + 1])
	{
		env[pos] = env[pos + 1];
		pos++;
	}
	env[pos] = NULL;
}

static void	unset_single_var(char *var_name, char **env)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(var_name);
	while (env[j])
	{
		if (!ft_strncmp(var_name, env[j], len)
			&& (env[j][len] == '=' || env[j][len] == '\0'))
		{
			free(env[j]);
			shift_env_vars(env, j);
			break ;
		}
		j++;
	}
}

int	builtin_unset(t_shell *sh, t_cmd *cmd)
{
	int	i;

	if (!sh || !cmd || !cmd->argv)
		return (1);
	i = 1;
	while (cmd->argv[i])
	{
		unset_single_var(cmd->argv[i], sh->our_envp);
		i++;
	}
	sh->last_status = 0;
	return (0);
}
