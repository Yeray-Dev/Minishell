/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:02:12 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 10:10:13 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_handler = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	t_shell;

	(void)argc;
	(void)argv;
	init_signals();
	t_shell.our_envp = duplicate_envp(envp);
	t_shell.last_status = 0;
	t_shell.exit_status = 0;
	t_shell.cd_home = NULL;
	t_shell.line = NULL;
	t_shell.list_token.top = NULL;
	t_shell.list_token.last = NULL;
	t_shell.list_token.shell = &t_shell;
	t_shell.cmd_list.top = NULL;
	t_shell.cmd_list.last = NULL;
	while (1)
	{
		g_handler = 0;
		t_shell.line = readline("MiniShell: > ");
		if (signal_proccess(&t_shell) == 1)
			continue ;
		else if (signal_proccess(&t_shell) == -1)
			break ;
		parser(&t_shell);
		execute_commands(&t_shell);
		free_cmd_list(&t_shell.cmd_list);
		free(t_shell.line);
	}
	free_dblptr(t_shell.our_envp);
	return (0);
}
