/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:41:43 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:41:43 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

t_exec_cmd	*init_exec_cmd(t_cmd *cmd)
{
	t_exec_cmd	*new;

	new = malloc(sizeof(t_exec_cmd));
	new->argv = cmd->argv;
	new->path = cmd->path;
	new->infile_fd = -1;
	new->outfile_fd = -1;
	new->builtin_type = cmd->builtin_type;
	new->is_builtin = (cmd->builtin_type != BI_NONE);
	new->original = cmd;
	new->next = NULL;
	return (new);
}

t_exec	*init_exec_struct(t_shell *sh, t_cmd *cmd_list)
{
	t_exec	*exec;
	(void)sh;
	exec = malloc(sizeof(t_exec));
	exec->n_cmds = count_cmds(cmd_list);
	exec->n_pipes = exec->n_cmds - 1;
	exec->pids = malloc(sizeof(pid_t) * exec->n_cmds);
	exec->pipes = NULL;
	if (exec->n_pipes > 0)
		exec->pipes = malloc(sizeof(int *) * exec->n_pipes);
	exec->cmds = NULL;
	return (exec);
}

void	build_exec_cmd_list(t_exec *exec, t_cmd *cmd_list)
{
	t_exec_cmd	*prev;
	t_exec_cmd	*new;

	prev = NULL;
	while (cmd_list)
	{
		new = init_exec_cmd(cmd_list);
		if (!exec->cmds)
			exec->cmds = new;
		if (prev)
			prev->next = new;
		prev = new;
		cmd_list = cmd_list->next;
	}
}

t_exec	*init_exec(t_shell *sh)
{
	t_exec	*exec;

	exec = init_exec_struct(sh, sh->cmd_list.top);
	build_exec_cmd_list(exec, sh->cmd_list.top);
	return (exec);
}
