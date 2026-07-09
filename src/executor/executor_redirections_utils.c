/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:34:44 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/20 14:24:31 by jugarcia         ###   ########.fr       */
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

int	apply_redirections_utils(int last_out_failed, t_redir *current_redir)
{
	(void)last_out_failed;
	while (current_redir)
	{
		if (current_redir->type == REDIR_TYPE_IN)
		{
			if (redirect_input(current_redir->file) < 0)
				return (1);
		}
		else
		{
			if (redirect_output(current_redir->file,
					current_redir->type == REDIR_TYPE_APPEND) < 0)
				return (1);
		}
		current_redir = current_redir->next;
	}
	return (0);
}

static char	*heredoc_readline(void)
{
	char	c;
	char	buf[2];
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	write(1, "> ", 2);
	buf[1] = '\0';
	while (read(0, &c, 1) == 1)
	{
		if (c == '\n')
			return (line);
		buf[0] = c;
		tmp = ft_strjoin(line, buf);
		free(line);
		line = tmp;
		if (!line)
			return (NULL);
	}
	free(line);
	return (NULL);
}

int	read_heredoc_loop(t_cmd *cmd, int *hd_pipe)
{
	char	*line;

	g_handler = 0;
	set_signal(SIGINT, handler_heredoc);
	while (1)
	{
		line = heredoc_readline();
		if (!line)
		{
			if (g_handler == 1)
				return (set_signal(SIGINT, handler_readline), 130);
			break ;
		}
		if (ft_strcmp(line, cmd->heredoc_word) == 0)
			return (free(line), set_signal(SIGINT, handler_readline), 0);
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
	}
	set_signal(SIGINT, handler_readline);
	return (0);
}
