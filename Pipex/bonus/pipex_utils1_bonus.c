/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:09:44 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/18 10:29:20 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fd(t_fd fd)
{
	close(fd.fd_pip[0]);
	close(fd.fd_pip[1]);
	close(fd.out);
}

void	change_fd(int fd, int oldfd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Dup2 failed");
	close(oldfd);
}

static void	write_to_heredoc(int fd, char *delimiter)
{
	char	*line;
	char	*delim_nl;

	delim_nl = ft_strjoin(delimiter, "\n");
	if (!delim_nl)
		return ;
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, delim_nl, ft_strlen(delim_nl)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
	free(delim_nl);
}

void	fd_heredoc(char *delimiter)
{
	int	tmp;

	if (access("/tmp/heredoc", F_OK) == 0)
		unlink("/tmp/heredoc");
	tmp = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp < 0)
		return ;
	write_to_heredoc(tmp, delimiter);
	close(tmp);
	tmp = open("/tmp/heredoc", O_RDONLY);
	if (tmp < 0)
		return ;
	dup2(tmp, STDIN_FILENO);
	close(tmp);
}

void	check_fd_in(char **av, int ac, int *i, t_fd *fd)
{
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		check_args(ac, 1);
		*i = 3;
		fd_heredoc(av[2]);
		fd->in = STDIN_FILENO;
		fd->out = set_file(av[ac - 1], 2);
	}
	else
	{
		check_args(ac, 2);
		*i = 2;
		fd->in = set_file(av[1], 0);
		fd->out = set_file(av[ac - 1], 1);
	}
}
