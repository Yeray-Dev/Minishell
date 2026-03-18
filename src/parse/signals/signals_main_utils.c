/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:03:55 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 10:21:16 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_proccess(t_shell *sh)
{
	if (sh->line == NULL)
		return (-1);
	if (g_handler == 1)
	{
		sh->last_status = 1;
		g_handler = 0;
		free(sh->line);
		return (1);
	}
	return (0);
}
