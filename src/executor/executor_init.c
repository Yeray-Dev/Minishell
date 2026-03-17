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
	if (!new)
		return (NULL);
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

t_exec	*init_exec_struct(t_cmd *cmd_list)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->n_cmds = count_cmds(cmd_list);
	exec->n_pipes = exec->n_cmds - 1;
	exec->pids = malloc(sizeof(pid_t) * exec->n_cmds);
	if (!exec->pids)
	{
		free(exec);
		return (NULL);
	}
	exec->pipes = NULL;
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
		if (!new)
			return ;
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

	exec = init_exec_struct(sh->cmd_list.top);
	if (!exec)
		return (NULL);
	if (exec->n_pipes > 0)
	{
		exec->pipes = malloc(sizeof(int *) * exec->n_pipes);
		if (!exec->pipes)
		{
			free(exec->pids);
			free(exec);
			return (NULL);
		}
	}
	build_exec_cmd_list(exec, sh->cmd_list.top);
	return (exec);
}
