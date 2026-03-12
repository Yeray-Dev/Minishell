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
		fprintf(stderr, "minishell: cd: too many arguments\n");
		sh->last_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_shell *sh, t_cmd *cmd)
{
	char	*path;

	if (check_multiple_args(cmd, sh))
		return (1);
	if (!cmd->argv[1])
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		sh->last_status = 1;
		return (1);
	}
	sh->last_status = 0;
	return (0);
}
