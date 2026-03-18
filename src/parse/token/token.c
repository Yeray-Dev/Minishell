/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:16:17 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 10:40:23 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_subtr(int start, int end, t_list_token *l_token )
{
	char	*new_token;

	if (start == -1)
		return (-1);
	if (end - start > 0)
	{
		new_token = ft_substr(l_token->shell->line, start, end - start);
		token_add_list(l_token, new_token);
		free(new_token);
	}
	return (0);
}

static int	token_stract_tokens(t_list_token *l_token)
{
	int		i;
	int		start;
	int		end;
	int		*array_index;

	i = 0;
	while (l_token->shell->line[i] == ' ')
		i++;
	while (l_token->shell->line[i] != '\0')
	{
		array_index = special_token(l_token->shell->line, l_token, &i);
		start = array_index[0];
		end = array_index[1];
		i = array_index[2];
		if (token_subtr(start, end, l_token) == -1)
			return (-1);
		while (l_token->shell->line[i] == ' ')
			i++;
		if (l_token->last)
			l_token->last->type = TOKEN_CMD;
	}
	return (0);
}

void	token_add_list(t_list_token *list_token, char *new_token)
{
	t_tokens	*token;

	if (!list_token || !new_token)
		return ;
	token = malloc(sizeof(t_tokens));
	if (!token)
		return ;
	token->name = ft_strdup(new_token);
	if (!token->name)
	{
		free(token);
		return ;
	}
	token->next = NULL;
	if (list_token->top == NULL)
	{
		list_token->top = token;
		list_token->last = token;
	}
	else
	{
		list_token->last->next = token;
		list_token->last = token;
	}
}

int	init_token(t_list_token *list_token)
{
	if (list_token->shell->line != NULL)
		return (token_stract_tokens(list_token));
	return (0);
}
