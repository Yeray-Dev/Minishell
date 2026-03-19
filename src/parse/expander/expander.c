/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:25:06 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 21:40:13 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_next(char *raw, int *i, t_shell *sh)
{
	if (raw[*i] == '\'')
		return (++(*i), expand_in_single(raw, i));
	if (raw[*i] == '"')
		return (++(*i), expand_in_double(raw, i, sh));
	if (raw[*i] == '$')
		return (expand_var(raw, i, sh));
	return (str_append_char(NULL, raw[(*i)++]));
}

static char	*get_env_value(char *name, char **envp, int status)
{
	size_t	len;
	int		i;

	if (!name || !name[0])
		return (ft_strdup(""));
	if (name[0] == '?' && !name[1])
		return (ft_itoa(status));
	len = ft_strlen(name);
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
	return (ft_strdup(""));
}

char	*expand_var(char *raw, int *i, t_shell *sh)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (raw[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->last_status));
	}
	start = *i;
	while (raw[*i] && raw[*i] != ' ' && raw[*i] != '$' && raw[*i] != '"'
		&& raw[*i] != '\'' && raw[*i] != '/' && raw[*i] != '|'
		&& raw[*i] != '<' && raw[*i] != '>' && raw[*i] != '=')
		(*i)++;
	name = ft_substr(raw, start, *i - start);
	if (!name[0])
	{
		free(name);
		return (ft_strdup("$"));
	}
	val = get_env_value(name, sh->our_envp, sh->last_status);
	free(name);
	return (val);
}

static char	*expand_token(char *raw, t_shell *sh)
{
	char	*res;
	char	*part;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (raw[i])
	{
		part = expand_next(raw, &i, sh);
		res = str_join_free(res, part);
	}
	return (res);
}

void	expand_token_list(t_list_token *list, t_shell *sh)
{
	t_tokens	*tok;
	t_tokens	*prev;
	char		*expanded;
	int			pure_var;

	tok = list->top;
	prev = NULL;
	while (tok)
	{
		if (tok->type == TOKEN_CMD)
		{
			pure_var = !has_quotes(tok->name);
			expanded = expand_token(tok->name, sh);
			free(tok->name);
			tok->name = expanded;
			if (pure_var && tok->name[0] == '\0')
			{
				tok = remove_token(list, prev, tok);
				continue ;
			}
		}
		prev = tok;
		tok = tok->next;
	}
}
