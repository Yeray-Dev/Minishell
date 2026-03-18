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

static int	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redirect_output(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void	read_heredoc_loop(t_cmd *cmd, int *hd_pipe)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_word) == 0)
		{
			free(line);
			break ;
		}
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
	}
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
	t_redir	*r;
	int		last_out_failed;

	(void)cmd;
	if (!original)
		return (0);
	r = original->redirs;
	last_out_failed = 0;
	while (r)
	{
		if (r->type == REDIR_TYPE_IN)
		{
			if (redirect_input(r->file) < 0)
				return (1);
		}
		else
		{
			if (redirect_output(r->file, r->type == REDIR_TYPE_APPEND) < 0)
				last_out_failed = 1;
			else
				last_out_failed = 0;
		}
		r = r->next;
	}
	if (original->is_heredoc && original->heredoc_fd != -1)
	{
		dup2(original->heredoc_fd, STDIN_FILENO);
		close(original->heredoc_fd);
	}
	if (last_out_failed)
		return (1);
	return (0);
}
