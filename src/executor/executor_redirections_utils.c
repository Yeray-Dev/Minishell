/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:34:44 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 21:35:40 by yblanco-         ###   ########.fr       */
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
				last_out_failed = 1;
			else
				last_out_failed = 0;
		}
		current_redir = current_redir->next;
	}
	return (last_out_failed);
}
