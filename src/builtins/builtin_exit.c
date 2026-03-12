/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:39:28 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:39:28 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_exit_invalid_arg(t_shell *sh, char *arg)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	sh->last_status = 2;
}

static void handle_exit_too_many_args(t_shell *sh)
{
	printf("minishell: exit: too many arguments\n");
	sh->last_status = 1;
}

void builtin_exit(t_shell *sh, t_cmd *cmd)
{
	long long exit_code;
	int invalid;

	printf("exit\n");

	if (cmd->argv[1] && cmd->argv[2])
	{
		handle_exit_too_many_args(sh);
		return;
	}

	if (cmd->argv[1])
	{
		exit_code = atoi_overflow(cmd->argv[1], &invalid);
		if (invalid)
		{
			handle_exit_invalid_arg(sh, cmd->argv[1]);
			exit(2);
		}
		exit((int)(exit_code % 256));
	}
	exit(sh->last_status);
}
