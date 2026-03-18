/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:27:36 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 09:40:02 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*str_append_char(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (str_join_free(s, ft_strdup(buf)));
}

t_tokens	*remove_token(t_list_token *list, t_tokens *prev, t_tokens *tok)
{
	t_tokens	*next;

	next = tok->next;
	if (prev == NULL)
		list->top = next;
	else
		prev->next = next;
	if (list->last == tok)
		list->last = prev;
	free(tok->name);
	free(tok);
	return (next);
}
