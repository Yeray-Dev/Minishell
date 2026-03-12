/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:34:53 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:34:53 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static t_exec	*prepare_exec(t_shell *sh)
{
	t_cmd	*first;
	t_exec	*exec;
	int		i;
	t_exec	**pipes;

	first = sh->cmd_list_top;
	if (first && !first->next && first->builtin_type != BI_NONE)
	{
		exec_builtin(sh, first);
		return (NULL);
	}
	exec = init_exec(sh);
	if (!exec)
		return (NULL);
	i = 0;
	pipes = exec->pipes;
	while (i < exec->n_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) < 0)
			perror("pipe");
		i++;
	}
	return (exec);
}

void	execute_commands(t_shell *sh)
{
	t_exec	*exec;

	exec = prepare_exec(sh);
	if (!exec)
		return ;
	executor_loop(sh, exec);
	wait_children(sh, exec);
	cleanup_exec(exec);
}
