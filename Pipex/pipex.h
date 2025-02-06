/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:18:56 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/06 18:18:06 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "gnl/get_next_line_bonus.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
#include <stdio.h>

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

void	ft_cmd_add(t_cmd **list, char *argv);
void	ft_pipex(t_cmd *cmds, t_fd *fd, char **env);
void	execute_cmd(t_cmd *cmd, char **env);
char	*get_path(char *cmd, char **env);
void	free_cmds(t_cmd *cmds);
int		set_file(char *file, int mode);
void	*free_paths(char **paths);

#endif