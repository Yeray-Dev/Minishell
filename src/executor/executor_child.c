/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:42:40 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:42:40 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_shell *sh, t_exec_cmd *cmd, int i, t_exec *exec)
{
	setup_pipes(exec, i);

	if (apply_redirections(cmd, cmd->original))
		exit(1);

	if (cmd->is_builtin)
	{
		exec_builtin(sh, cmd->original);
		exit(sh->last_status);
	}

	cmd->path = resolve_path(cmd->argv[0], sh->our_envp);
	if (!cmd->path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
		exit(127);
	}

	execve(cmd->path, cmd->argv, sh->our_envp);
	perror(cmd->argv[0]);
	exit(127);
}

