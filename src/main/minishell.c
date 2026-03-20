/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:02:12 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/20 11:46:34 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_handler = 0;

static void	init_struct(t_shell *t_sh, char **envp)
{
	t_sh->our_envp = duplicate_envp(envp);
	t_sh->last_status = 0;
	t_sh->exit_status = 0;
	t_sh->cd_home = NULL;
	t_sh->line = NULL;
	t_sh->list_token.top = NULL;
	t_sh->list_token.last = NULL;
	t_sh->cmd_list.top = NULL;
	t_sh->cmd_list.last = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	t_shell;

	(void)argc;
	(void)argv;
	init_signals();
	init_struct(&t_shell, envp);
	t_shell.list_token.shell = &t_shell;
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
