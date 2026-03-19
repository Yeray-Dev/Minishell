/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:54:55 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 08:43:46 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_tokes(t_list_token *s_list_token)
{
	size_t		count;
	t_tokens	*temp;

	temp = s_list_token->top;
	count = 0;
	while (temp != NULL && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_REDIRECTIONS)
		{
			temp = temp->next;
			if (temp != NULL)
				temp = temp->next;
		}
		else
		{
			count++;
			temp = temp->next;
		}
	}
	return (count);
}

static void	add_redir(t_cmd *cmd, int type, char *file)
{
	t_redir	*redir;
	t_redir	*last;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = redir;
}

void	set_cmd_link_type(t_cmd *new_cmd, t_tokens **end_token)
{
	if (!end_token || !*end_token)
		return ;
	if ((*end_token)->type == TOKEN_PIPE)
		new_cmd->has_pipe = 1;
	else if ((*end_token)->type == TOKEN_REDIRECTIONS)
	{
		if (ft_strncmp((*end_token)->name, "<<", 2) == 0 && (*end_token)->next)
		{
			new_cmd->heredoc_word = ft_strdup((*end_token)->next->name);
			new_cmd->is_heredoc = 1;
		}
		else if (ft_strncmp((*end_token)->name, ">>", 2) == 0
			&& (*end_token)->next)
			add_redir(new_cmd, REDIR_TYPE_APPEND, (*end_token)->next->name);
		else if (ft_strncmp((*end_token)->name, "<", 1) == 0
			&& (*end_token)->next)
			add_redir(new_cmd, REDIR_TYPE_IN, (*end_token)->next->name);
		else if (ft_strncmp((*end_token)->name, ">", 1) == 0
			&& (*end_token)->next)
			add_redir(new_cmd, REDIR_TYPE_OUT, (*end_token)->next->name);
		*end_token = (*end_token)->next;
	}
}

void	create_cmd_utils(t_list_token *s_list_token, t_cmd *current_cmd)
{
	int	i;

	i = 0;
	while (s_list_token->top != NULL
		&& s_list_token->top->type != TOKEN_PIPE)
	{
		if (s_list_token->top->type == TOKEN_REDIRECTIONS)
		{
			set_cmd_link_type(current_cmd, &s_list_token->top);
			if (s_list_token->top != NULL)
				s_list_token->top = s_list_token->top->next;
		}
		else
		{
			current_cmd->argv[i++] = ft_strdup(s_list_token->top->name);
			s_list_token->top = s_list_token->top->next;
		}
	}
	current_cmd->argv[i] = NULL;
	if (s_list_token->top != NULL
		&& s_list_token->top->type == TOKEN_PIPE)
	{
		current_cmd->has_pipe = 1;
		s_list_token->top = s_list_token->top->next;
	}
}
