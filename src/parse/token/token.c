#include "minishell.h"

static void	token_stract_tokens(char *line, t_list_token *list_token,
	char **our_envp)
{
	int		i;
	int		start;
	int		end;
	char	*new_token;
	int		*array_index;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\0')
	{
		array_index = special_token(line, list_token, our_envp, &i);
		start = array_index[0];
		end = array_index[1];
		i = array_index[2];
		if (end - start > 0)
		{
			new_token = ft_substr(line, start, end - start);
			token_add_list(list_token, new_token);
			free(new_token);
		}
		while (line[i] == ' ')
			i++;
		if (list_token->last)
			list_token->last->type = TOKEN_CMD;
	}
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

int	init_token(char *line, t_list_token *list_token, char **our_envp)
{
	if (line != NULL)
		token_stract_tokens(line, list_token, our_envp);
	return (1);
}
