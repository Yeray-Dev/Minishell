/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:40:13 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:40:13 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_one(t_shell *sh, char *arg, int *has_error)
{
	char	*name;
	int		idx;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*has_error = 1;
		return ;
	}
	name = get_var_name(arg);
	idx = env_get(sh->our_envp, name);
	if (ft_strchr(arg, '='))
	{
		if (env_set(&sh->our_envp, arg) != 0)
			*has_error = 1;
	}
	else
	{
		if (idx == -1)
			if (env_add_empty(&sh->our_envp, name) != 0)
				*has_error = 1;
	}
	free(name);
}

int	export_print(t_shell *sh)
{
	char	**sorted;
	int		i;

	sorted = env_copy(sh->our_envp);
	if (!sorted)
		return (1);
	env_sort(sorted);
	i = 0;
	while (sorted[i])
	{
		print_export(sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	export_args(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	has_error;

	i = 1;
	has_error = 0;
	while (cmd->argv[i])
	{
		export_one(sh, cmd->argv[i], &has_error);
		i++;
	}
	if (has_error == 0)
		return (0);
	return (1);
}

int	builtin_export(t_shell *sh, t_cmd *cmd)
{
	if (!cmd->argv[1])
		sh->last_status = export_print(sh);
	else
		sh->last_status = export_args(sh, cmd);
	return (sh->last_status);
}
