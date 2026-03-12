/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:16:58 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 15:16:58 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		cmd->builtin_type = BI_PWD;
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		cmd->builtin_type = BI_ECHO;
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		cmd->builtin_type = BI_ENV;
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		cmd->builtin_type = BI_EXPORT;
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		cmd->builtin_type = BI_UNSET;
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		cmd->builtin_type = BI_CD;
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		cmd->builtin_type = BI_EXIT;
	else
		cmd->builtin_type = BI_NONE;
}

static int	exec_builtin_helper(t_shell *sh, t_cmd *cmd)
{
	if (cmd->builtin_type == BI_PWD)
		return (builtin_pwd(sh, cmd));
	if (cmd->builtin_type == BI_ECHO)
		return (builtin_echo(sh, cmd));
	if (cmd->builtin_type == BI_ENV)
		return (builtin_env(sh, cmd));
	if (cmd->builtin_type == BI_EXPORT)
		return (builtin_export(sh, cmd));
	if (cmd->builtin_type == BI_UNSET)
		return (builtin_unset(sh, cmd));
	if (cmd->builtin_type == BI_CD)
		return (builtin_cd(sh, cmd));
	if (cmd->builtin_type == BI_EXIT)
	{
		builtin_exit(sh, cmd);
		return (sh->last_status);
	}
	return (1);
}

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	int	status;

	if (!cmd || !sh)
		return (1);
	detect_builtin(cmd);
	status = exec_builtin_helper(sh, cmd);
	sh->last_status = status;
	return (status);
}
