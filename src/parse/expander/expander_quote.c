/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:27:40 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 09:38:28 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_in_double(char *raw, int *i, char *res, t_shell *sh)
{
	char	*val;

	while (raw[*i] && raw[*i] != '"')
	{
		if (raw[*i] == '$')
		{
			val = expand_var(raw, i, sh);
			res = str_join_free(res, val);
		}
		else
			res = str_append_char(res, raw[(*i)++]);
	}
	if (raw[*i] == '"')
		(*i)++;
	return (res);
}

char	*expand_in_single(char *raw, int *i, char *res)
{
	while (raw[*i] && raw[*i] != '\'')
		res = str_append_char(res, raw[(*i)++]);
	if (raw[*i] == '\'')
		(*i)++;
	return (res);
}

int	has_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}
