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

static t_exec	*prepare_exec(t_shell *sh)
{
	t_cmd	*first;
	t_exec	*exec;

	first = sh->cmd_list.top;
	if (first && !first->next && first->builtin_type != BI_NONE)
	{
		exec_builtin(sh, first);
		return (NULL);
	}
	exec = init_exec(sh);
	if (!exec)
		return (NULL);
	create_pipes(exec);
	return (exec);
}

void	execute_commands(t_shell *sh)
{
	t_exec	*exec;
	int		status;

	status = handle_heredocs(&sh->cmd_list);
	if (status == 130)
	{
		sh->last_status = 130;
		return ;
	}
	exec = prepare_exec(sh);
	if (!exec)
		return ;
	executor_loop(sh, exec);
	close_all_pipes_in_parent(exec);
	wait_children(sh, exec);
	cleanup_exec(exec);
}
