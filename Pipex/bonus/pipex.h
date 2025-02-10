/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:18:56 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 10:53:15 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_fd
{
	int	in;
	int	out;
	int	fd_pip[2];
	int	pid;
}		t_fd;
typedef struct s_cmd
{
	char			**str;
	struct s_cmd	*next;
}					t_cmd;

char	**parse_arg(char *str);
void	ft_pipex(t_cmd *cmds, t_fd fd, char **env);
void	*free_paths(char **paths);
void	change_fd(int fd, int oldfd);
void	check_fd_in(char **av, int ac, int *i, t_fd *fd);
int		set_file(char *file, int mode);
void	check_args(int ac, int mode);

#endif