#include "pipex.h"


void	*free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_candidate;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
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

void	execute_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!env || !cmd->str[0])
		exit(1);
	path = get_path(cmd->str[0], env);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd->str[0], 2);
		exit(127);
	}
	execve(path, cmd->str, env);
	free(path);
	exit(1);
}

void	child_process(t_cmd *cmd, t_fd *fd, char **env, int mode)
{
	if (mode == 1)
	{
		dup2(fd->in, STDIN_FILENO);
		dup2(fd->fd_pip[1], STDOUT_FILENO);
		close(fd->fd_pip[0]);
	}
	else
	{
		dup2(fd->fd_pip[0], STDIN_FILENO);
		dup2(fd->out, STDOUT_FILENO);
		close(fd->fd_pip[1]);
	}
	execute_cmd(cmd, env);
}

void	ft_pipex(t_cmd *cmds, t_fd *fd, char **env)
{
	if (pipe(fd->fd_pip) == -1)
		exit(1);
	fd->pid = fork();
	if (fd->pid == -1)
		exit(1);
	if (fd->pid == 0)
		child_process(cmds, fd, env, 1);
	else
	{
		fd->pid = fork();
		if (fd->pid == -1)
			exit(1);
		if (fd->pid == 0)
			child_process(cmds->next, fd, env, 2);
		else
		{
			close(fd->fd_pip[0]);
			close(fd->fd_pip[1]);
			waitpid(fd->pid, NULL, 0);
			waitpid(fd->pid, NULL, 0);
		}
	}
}
