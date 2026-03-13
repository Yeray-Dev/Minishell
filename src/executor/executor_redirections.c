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

	if (append != 0)
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

int	apply_redirections(t_exec_cmd *cmd, t_cmd *original)
{
	(void)cmd;
	if (!original)
		return (0);

	// Redirección de entrada desde archivo
	if (original->infile)
	{
		if (redirect_input(original->infile) < 0)
			return (1);
	}

	// Redirección de entrada desde heredoc
	if (original->is_heredoc && original->heredoc_word)
	{
		int hd_pipe[2];

		if (pipe(hd_pipe) < 0)
		{
			perror("pipe");
			return (1);
		}

		// Escribir el contenido del heredoc en el pipe
		write(hd_pipe[1], original->heredoc_word, strlen(original->heredoc_word));
		write(hd_pipe[1], "\n", 1); // salto de línea final
		close(hd_pipe[1]);

		// Redirigir stdin del child al pipe del heredoc
		dup2(hd_pipe[0], STDIN_FILENO);
		close(hd_pipe[0]);
	}

	// Redirección de salida
	if (original->outfile)
	{
		if (redirect_output(original->outfile, original->append) < 0)
			return (1);
	}

	return (0);
}

