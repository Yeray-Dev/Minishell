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

static void	check_cmd(t_exec_cmd *cmd)
{
	if (!cmd->path)
	{
		if (ft_strchr(cmd->argv[0], '/') && access(cmd->argv[0], F_OK) == 0)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	exec_child(t_shell *sh, t_exec_cmd *cmd, int i, t_exec *exec)
{
	int	err;

	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
	setup_pipes(exec, i);
	if (cmd->is_builtin)
	{
		exec_builtin(sh, cmd->original);
		exit(sh->last_status);
	}
	if (apply_redirections(cmd, cmd->original))
		exit(1);
	cmd->path = resolve_path(cmd->argv[0], sh->our_envp);
	check_cmd(cmd);
	execve(cmd->path, cmd->argv, sh->our_envp);
	err = errno;
	perror(cmd->argv[0]);
	if (err == EACCES || err == EISDIR)
		exit(126);
	exit(127);
}
