/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:58:28 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 10:59:54 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	listsize(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	wait_childern(int *pids, int size)
{
	int	status;
	int	i;

	i = 0;
	while (i < size)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("Waitpid");
			exit(1);
		}
		status = WEXITSTATUS(status);
		if (status == 127 && i == size - 1)
			exit(status);
		i++;
	}
	free(pids);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_candidate;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/') || !ft_strncmp(cmd, "./", 2))
		return (ft_strdup(cmd));
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path_candidate = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_candidate, cmd);
		free(path_candidate);
		if (access(full_path, X_OK) == 0)
			return (free_paths(paths), full_path);
		free(full_path);
	}
	free_paths(paths);
	return (NULL);
}

void	child_exec(t_cmd *cmds, t_fd fd, char **env)
{
	char	*path;

	path = NULL;
	if (fd.in != 0)
		if (dup2(fd.in, 0) == -1)
			perror("Dup2 Failed");
	if (cmds->next)
		change_fd(fd.fd_pip[1], fd.fd_pip[0]);
	else
		change_fd(fd.out, fd.fd_pip[1]);
	close(fd.fd_pip[0]);
	path = get_path(cmds->str[0], env);
	if (!path)
	{
		ft_putstr_fd(cmds->str[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmds->str, env) == -1)
	{
		perror("failed execution");
		exit(1);
	}
}

void	ft_pipex(t_cmd *cmds, t_fd fd, char **env)
{
	int	*pids;
	int	i;

	i = 0;
	pids = malloc(sizeof(int) * listsize(cmds));
	if (!pids)
		return ;
	while (cmds)
	{
		pipe(fd.fd_pip);
		fd.pid = fork();
		if (fd.pid == 0)
			child_exec(cmds, fd, env);
		else
		{
			pids[i++] = fd.pid;
			close(fd.fd_pip[1]);
			if (!cmds->next)
				break ;
			fd.in = fd.fd_pip[0];
		}
		cmds = cmds->next;
	}
	close(fd.in);
	wait_childern(pids, i);
}
