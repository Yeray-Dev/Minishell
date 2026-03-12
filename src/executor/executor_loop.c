/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:40:19 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:40:19 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor_loop(t_shell *sh, t_exec *exec)
{
	t_exec_cmd	*cmd;
	int			i;

	cmd = exec->cmds;
	i = 0;
	while (cmd)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] < 0)
			perror("fork");
		else if (exec->pids[i] == 0)
			exec_child(sh, cmd, i, exec);
		cmd = cmd->next;
		i++;
	}
}
