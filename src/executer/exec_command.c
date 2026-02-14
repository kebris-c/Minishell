/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:40 by kebris-c          #+#    #+#             */
/*   Updated: 2026/01/15 18:35:28 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static char	*join_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static char	*search_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (ft_free_matrix(paths), full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	return (ft_free_matrix(paths), NULL);
}

static char	*resolve_path(char *cmd)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			errno = ENOENT;
			return (NULL);
		}
		if (access(cmd, X_OK) == -1)
		{
			errno = EACCES;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (search_in_path(cmd));
}

void	exec_command(t_exec_cmds *s, t_shell *sh)
{
	char	*cmd_path;

	cmd_path = resolve_path(s->cmd->av[0]);
	if (!cmd_path)
	{
		if (errno == EACCES)
			(perror(s->cmd->av[0]), exit(126));
		else
		{
			ft_putstr_fd(s->cmd->av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	execve(cmd_path, s->cmd->av, sh->env);
	perror("execve");
	if (cmd_path)
		free(cmd_path);
	exit(126);
}
