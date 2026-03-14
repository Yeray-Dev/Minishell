/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:35:38 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:35:38 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_children(t_shell *sh, t_exec *exec)
{
	int	i;
	int	status;

	i = 0;
	while (i < exec->n_cmds)
	{
		status = 0;
		waitpid(exec->pids[i], &status, 0);
		if (WIFEXITED(status))
			sh->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sh->last_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				write(2, "\n", 1);
		}
		i++;
	}
}

void	cleanup_exec(t_exec *exec)
{
	t_exec_cmd	*cmd;
	t_exec_cmd	*tmp;
	int			**pipes;

	if (!exec)
		return ;
	pipes = exec->pipes;
	cmd = exec->cmds;
	while (exec->n_pipes-- > 0)
		free(pipes[exec->n_pipes]);
	free(pipes);
	free(exec->pids);
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	free(exec);
}
