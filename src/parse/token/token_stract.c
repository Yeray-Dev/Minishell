#include "minishell.h"

static int	handle_variable(char *line, int *i, char **our_envp,
							t_list_token *lst, int *end)
{
	int	j;

	if (line[*i] != '$' || (*i > 0 && line[*i - 1] == '/'))
		return (0);
	j = stract_variables(line, i, our_envp, lst->shell);
	if (j == 0)
	{
		(*i)++;
		return (1);
	}
	if (*i > 0)
		(*i)--;
	*end = *i;
	return (1);
}

static int	handle_quote(char *line, int *i, char **our_envp,
						t_list_token *lst, int *end)
{
	if (!token_is_quote(line, i, our_envp, lst))
		return (0);
	*end = *i;
	return (1);
}

static int	handle_pipe_redirect(char *line, int *i, int *start, int *end,
								t_list_token *lst)
{
	if (!token_is_pipe(line, i, start, lst)
		&& !token_is_redirect(line, i, start, lst))
		return (0);
	while (line[*i] == ' ')
		(*i)++;
	*start = *i;
	*end = *start;
	return (1);
}

static int	*build_array(int start, int end, int i)
{
	static int	array_index[3];

	if (end == start)
		end = i;
	array_index[0] = start;
	array_index[1] = end;
	array_index[2] = i;
	return (array_index);
}

int	*special_token(char *line, t_list_token *lst, char **our_envp, int *i)
{
	int	start;
	int	end;

	start = *i;
	end = start;
	while ((line[*i] != ' ' || (*i > 0 && line[*i] == ' '
				&& line[*i - 1] == '/')) && line[*i] != '\0')
	{
		if (handle_variable(line, i, our_envp, lst, &end))
			break ;
		if (handle_quote(line, i, our_envp, lst, &end))
			break ;
		if (handle_pipe_redirect(line, i, &start, &end, lst))
			continue ;
		if (line[*i] != '\0')
			(*i)++;
	}
	return (build_array(start, end, *i));
}
