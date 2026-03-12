/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:42:29 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:42:29 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_dblptr(paths);
	return (result);
}

static void	exec_child_bultins(char **tokens, char **envp)
{
	char	*path;
	int		len;

	path = get_command_path(tokens[0], envp);
	if (!path || execve(path, tokens, envp) == -1)
	{
		write(2, "minishell: ", 11);
		len = ft_strlen(tokens[0]);
		write(2, tokens[0], len);
		write(2, ": command not found\n", 20);
		if (path)
			free(path);
		free_dblptr(envp);
		exit(127);
	}
	free(path);
	exit(0);
}

void	fork_and_exec(char **tokens, char **envp, int *exit_status)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		*exit_status = 1;
		return ;
	}
	if (pid == 0)
		exec_child_bultins(tokens, envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
}
