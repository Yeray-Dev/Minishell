/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:16:14 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 08:16:15 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_quote(char *line, int *i)
{
	char	quote_char;

	if (line[*i] != QUOTES && line[*i] != QUOTE)
		return (0);
	quote_char = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (!line[*i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (-1);
	}
	(*i)++;
	return (1);
}

int	token_is_pipe(char *line, int *i, int *start, t_list_token *list_token)
{
	char	*new_token;

	if (line[*i] == PIPE)
	{
		if (*i > *start)
		{
			new_token = ft_substr(line, *start, *i - *start);
			token_add_list(list_token, new_token);
			free(new_token);
		}
		(*i)++;
		*start = *i;
		new_token = ft_substr(line, *i - 1, 1);
		token_add_list(list_token, new_token);
		list_token->last->type = TOKEN_PIPE;
		free(new_token);
		return (1);
	}
	return (0);
}

void	token_is_double_redirect(char *line, int *i, int *start,
	t_list_token *list_token)
{
	char	*new_token;

	if (*i > *start)
	{
		new_token = ft_substr(line, *start, *i - *start);
		token_add_list(list_token, new_token);
		free(new_token);
	}
	(*i) += 2;
	*start = *i;
	new_token = ft_substr(line, *i - 2, 2);
	token_add_list(list_token, new_token);
	list_token->last->type = TOKEN_REDIRECTIONS;
	free(new_token);
}

int	token_is_redirect(char *line, int *i, int *start, t_list_token *list_token)
{
	char	*new_token;

	if (ft_strncmp(&line[*i], "<<", 2) == 0
		|| ft_strncmp(&line[*i], ">>", 2) == 0)
	{
		token_is_double_redirect(line, i, start, list_token);
		return (1);
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		if (*i > *start)
		{
			new_token = ft_substr(line, *start, *i - *start);
			token_add_list(list_token, new_token);
			free(new_token);
		}
		(*i)++;
		*start = *i;
		new_token = ft_substr(line, *i - 1, 1);
		token_add_list(list_token, new_token);
		list_token->last->type = TOKEN_REDIRECTIONS;
		free(new_token);
		return (1);
	}
	return (0);
}

void	free_token_list(t_list_token *list_token)
{
	t_tokens	*current;
	t_tokens	*next;

	current = list_token->top;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	list_token->top = NULL;
	list_token->last = NULL;
}
