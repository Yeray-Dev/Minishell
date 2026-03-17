/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:42:10 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:42:10 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_get(char **env, const char *key)
{
	int		i;
	size_t	len;

	if (!env || !key)
		return (-1);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	env_replace(char **env, int idx, const char *var)
{
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
		return (-1);
	free(env[idx]);
	env[idx] = new_var;
	return (0);
}

static int	env_add(char ***env, const char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	while (*env && (*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (-1);
	i = 0;
	while (*env && (*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
	{
		free(new_env);
		return (-1);
	}
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	env_add_empty(char ***env, const char *name)
{
	char	*tmp;
	int		ret;

	tmp = ft_strjoin((char *)name, "=");
	if (!tmp)
		return (-1);
	ret = env_add(env, tmp);
	free(tmp);
	return (ret);
}

int	env_set(char ***env, const char *var)
{
	int		idx;
	char	*name;

	if (!env || !var)
		return (-1);
	name = get_var_name(var);
	if (!name)
		return (-1);
	idx = env_get(*env, name);
	free(name);
	if (idx != -1)
		return (env_replace(*env, idx, var));
	return (env_add(env, var));
}
