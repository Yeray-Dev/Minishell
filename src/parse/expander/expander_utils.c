/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:27:36 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 21:40:22 by yblanco-         ###   ########.fr       */
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

char	**duplicate_envp(char **envp)
{
	int		len;
	char	**our_envp;

	len = 0;
	while (envp[len] != NULL)
		len++;
	our_envp = malloc(sizeof(char *) * (len + 1));
	if (!our_envp)
		return (NULL);
	len = 0;
	while (envp[len] != NULL)
	{
		our_envp[len] = ft_strdup(envp[len]);
		len++;
	}
	our_envp[len] = NULL;
	return (our_envp);
}
