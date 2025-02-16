/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:10:40 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/16 12:10:41 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_fd
{
	int				in;
	int				out;
	int				fd_pip[2];
	int				pid;
}					t_fd;
typedef struct s_cmd
{
	char			**str;
	struct s_cmd	*next;
}					t_cmd;

char				**parse_arg(char *str);
void				ft_pipex(t_cmd *cmds, t_fd fd, char **env, int *pids);
void				*free_paths(char **paths);
void				free_cmds(t_cmd **cmds);
void				free_arr(char **arr);
void				change_fd(int fd, int oldfd);
int					set_file(char *file, int mode);
void				close_fd(t_fd fd);

#endif