#include "minishell.h"

static char	*str_join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*str_append_char(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (str_join_free(s, ft_strdup(buf)));
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

static char	*expand_var(char *raw, int *i, t_shell *sh)
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
	val = get_env_value(name, sh->our_envp, sh->last_status);
	free(name);
	return (val);
}

static char	*expand_in_double(char *raw, int *i, char *res, t_shell *sh)
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

static char	*expand_in_single(char *raw, int *i, char *res)
{
	while (raw[*i] && raw[*i] != '\'')
		res = str_append_char(res, raw[(*i)++]);
	if (raw[*i] == '\'')
		(*i)++;
	return (res);
}

static char	*expand_token(char *raw, t_shell *sh)
{
	char	*res;
	char	*val;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (raw[i])
	{
		if (raw[i] == '\'')
		{
			i++;
			res = expand_in_single(raw, &i, res);
		}
		else if (raw[i] == '"')
		{
			i++;
			res = expand_in_double(raw, &i, res, sh);
		}
		else if (raw[i] == '$')
		{
			val = expand_var(raw, &i, sh);
			res = str_join_free(res, val);
		}
		else
			res = str_append_char(res, raw[i++]);
	}
	return (res);
}

void	expand_token_list(t_list_token *list, t_shell *sh)
{
	t_tokens	*tok;
	char		*expanded;

	tok = list->top;
	while (tok)
	{
		if (tok->type == TOKEN_CMD)
		{
			expanded = expand_token(tok->name, sh);
			free(tok->name);
			tok->name = expanded;
		}
		tok = tok->next;
	}
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
