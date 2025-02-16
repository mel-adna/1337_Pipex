/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:09:37 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/16 12:09:38 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_childern(int *pids, int size)
{
	int	status;
	int	i;

	i = 0;
	while (i < size)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			free(pids);
			perror("Waitpid");
			exit(1);
		}
		status = WEXITSTATUS(status);
		if (status == 127 && i == size - 1)
		{
			free(pids);
			exit(status);
		}
		i++;
	}
	free(pids);
	if (access("/tmp/heredoc", F_OK) == 0)
		unlink("/tmp/heredoc");
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
			return (free_arr(paths), full_path);
		free(full_path);
	}
	free_arr(paths);
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
	close_fd(fd);
	path = get_path(cmds->str[0], env);
	if (!path)
	{
		ft_putstr_fd(cmds->str[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmds->str, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmds->str[0], 2);
		exit(1);
	}
}

void	handle_parent(t_fd *fd, int *pids, int *i, t_cmd *cmds)
{
	pids[(*i)++] = fd->pid;
	close(fd->fd_pip[1]);
	if (fd->in != 0)
		close(fd->in);
	if (!cmds->next)
	{
		close(fd->fd_pip[0]);
		return ;
	}
	fd->in = fd->fd_pip[0];
}

void	ft_pipex(t_cmd *cmds, t_fd fd, char **env, int *pids)
{
	int	i;

	i = 0;
	pids = malloc(sizeof(int) * listsize(cmds));
	if (!pids)
		return ;
	while (cmds)
	{
		if (pipe(fd.fd_pip) == -1)
			exit(1);
		fd.pid = fork();
		if (fd.pid == 0)
			child_exec(cmds, fd, env);
		else
		{
			handle_parent(&fd, pids, &i, cmds);
			if (!cmds->next)
				break ;
		}
		cmds = cmds->next;
	}
	close(fd.out);
	wait_childern(pids, i);
}
