/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:13:43 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/20 12:14:42 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(t_shell *sh, const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)token, 2);
	ft_putstr_fd("'\n", 2);
	sh->last_status = 2;
	return (-1);
}

int	validate_syntax(t_list_token *list_token, t_shell *sh)
{
	t_tokens	*tok;

	tok = list_token->top;
	if (!tok)
		return (0);
	if (tok->type == TOKEN_PIPE)
		return (syntax_error(sh, "|"));
	while (tok)
	{
		if (tok->type == TOKEN_REDIRECTIONS)
		{
			if (!tok->next)
				return (syntax_error(sh, "newline"));
			if (tok->next->type == TOKEN_PIPE)
				return (syntax_error(sh, "|"));
			if (tok->next->type == TOKEN_REDIRECTIONS)
				return (syntax_error(sh, tok->next->name));
		}
		else if (tok->type == TOKEN_PIPE && tok->next
			&& tok->next->type == TOKEN_PIPE)
			return (syntax_error(sh, "|"));
		tok = tok->next;
	}
	return (0);
}
