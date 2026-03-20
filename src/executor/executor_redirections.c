/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 04:37:31 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 04:37:31 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc_loop(t_cmd *cmd, int *hd_pipe)
{
	char	*line;

	set_signal(SIGINT, handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line || g_handler == 1 || ft_strcmp(line, cmd->heredoc_word) == 0)
		{
			free(line);
			break ;
		}
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
	}
	set_signal(SIGINT, handler_readline);
}

void	handle_heredocs(t_list_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		hd_pipe[2];

	cmd = cmd_list->top;
	while (cmd)
	{
		if (cmd->is_heredoc && cmd->heredoc_word)
		{
			if (pipe(hd_pipe) < 0)
			{
				perror("pipe");
				cmd = cmd->next;
				continue ;
			}
			read_heredoc_loop(cmd, hd_pipe);
			close(hd_pipe[1]);
			cmd->heredoc_fd = hd_pipe[0];
		}
		cmd = cmd->next;
	}
}

int	apply_redirections(t_exec_cmd *cmd, t_cmd *original)
{
	int	last_out_failed;

	(void)cmd;
	if (!original)
		return (0);
	last_out_failed = apply_redirections_utils(0, original->redirs);
	if (last_out_failed == -1)
		return (1);
	if (original->is_heredoc && original->heredoc_fd != -1)
	{
		dup2(original->heredoc_fd, STDIN_FILENO);
		close(original->heredoc_fd);
	}
	if (last_out_failed)
		return (1);
	return (0);
}
