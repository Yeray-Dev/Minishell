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

static void	read_heredoc_loop(int *hd_pipe, char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = readline("> "); // o de esta otra forma se ve disitnto al ahcer doble ctrl c revisa las dos -> line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(hd_pipe[1], line, ft_strlen(line));
		free(line);
	}
}

static int	wait_for_heredoc_child(pid_t pid, int *hd_pipe)
{
	int		status;
	void	(*old_sigint)(int);

	old_sigint = signal(SIGINT, SIG_IGN);
	close(hd_pipe[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(hd_pipe[0]);
		return (-1);
	}
	return (0);
}

static int	read_heredoc_with_fork(t_cmd *cmd)
{
	pid_t	pid;
	int		hd_pipe[2];

	if (pipe(hd_pipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(hd_pipe[0]);
		read_heredoc_loop(hd_pipe, cmd->heredoc_word);
		close(hd_pipe[1]);
		exit(0);
	}
	else
	{
		if (wait_for_heredoc_child(pid, hd_pipe) < 0)
			return (-1);
		cmd->heredoc_fd = hd_pipe[0];
	}
	return (0);
}

void	handle_heredocs(t_list_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->top;
	while (cmd)
	{
		if (cmd->is_heredoc && cmd->heredoc_word)
		{
			if (read_heredoc_with_fork(cmd) < 0)
				cmd->heredoc_fd = -1;
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
