/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 08:42:53 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 08:44:04 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_cmd_list(t_list_cmd *list_cmd)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		i;

	cmd = list_cmd->top;
	while (cmd)
	{
		next = cmd->next;
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
		free_redirs(cmd->redirs);
		if (cmd->heredoc_word)
			free(cmd->heredoc_word);
		if (cmd->heredoc_fd != -1)
			close(cmd->heredoc_fd);
		free(cmd);
		cmd = next;
	}
	list_cmd->top = NULL;
	list_cmd->last = NULL;
}
