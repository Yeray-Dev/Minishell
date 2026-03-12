/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:39:42 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:39:42 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *sh, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	if (!sh || !sh->our_envp)
		return (1);
	i = 0;
	while (sh->our_envp[i])
	{
		printf("%s\n", sh->our_envp[i]);
		i++;
	}
	sh->last_status = 0;
	return (0);
}
