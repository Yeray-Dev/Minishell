/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:16:10 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 09:16:13 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote(char *line, int *i, int *end)
{
	int	ret;

	ret = token_is_quote(line, i);
	if (ret == 0)
		return (0);
	if (ret == -1)
		return (-1);
	*end = *i;
	return (1);
}

static int	handle_pipe_redirect(int *i, int *start, int *end,
								t_list_token *lst)
{
	if (!token_is_pipe(lst->shell->line, i, start, lst)
		&& !token_is_redirect(lst->shell->line, i, start, lst))
		return (0);
	while (lst->shell->line[*i] == ' ')
		(*i)++;
	*start = *i;
	*end = *start;
	return (1);
}

static int	*build_array(int start, int end, int i)
{
	static int	array_index[3];

	(void)end;
	array_index[0] = start;
	array_index[1] = i;
	array_index[2] = i;
	return (array_index);
}

int	*special_token(char *line, t_list_token *lst, int *i)
{
	int	start;
	int	end;
	int	ret;

	start = *i;
	end = start;
	while ((line[*i] != ' ' || (*i > 0 && line[*i] == ' '
				&& line[*i - 1] == '/')) && line[*i] != '\0')
	{
		ret = handle_quote(line, i, &end);
		if (ret == -1)
		{
			while (line[*i])
				(*i)++;
			return (build_array(-1, -1, *i));
		}
		if (ret == 1)
			continue ;
		if (handle_pipe_redirect(i, &start, &end, lst))
			continue ;
		if (line[*i] != '\0')
			(*i)++;
	}
	return (build_array(start, end, *i));
}
