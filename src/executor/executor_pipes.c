/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:38:17 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:38:17 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_pipes)
	{
		exec->pipes[i] = malloc(sizeof(int) * 2);
		if (!exec->pipes[i])
		{
			perror("malloc");
			return ;
		}
		if (pipe(exec->pipes[i]) < 0)
		{
			perror("pipe");
			free(exec->pipes[i]);
			exec->pipes[i] = NULL;
			return ;
		}
		i++;
	}
}

void	close_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->n_pipes)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}

void	setup_pipes(t_exec *exec, int i)
{
	int	j;

	if (i > 0)
		dup2(exec->pipes[i - 1][0], STDIN_FILENO);
	if (i < exec->n_cmds - 1)
		dup2(exec->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < exec->n_pipes)
	{
		close(exec->pipes[j][0]);
		close(exec->pipes[j][1]);
		j++;
	}
}

void	close_all_pipes_in_parent(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->n_pipes)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}
