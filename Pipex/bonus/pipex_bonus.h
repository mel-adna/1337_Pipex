/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:10:01 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/18 10:29:41 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>

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
void				free_arr(char **arr);
void				change_fd(int fd, int oldfd);
void				check_fd_in(char **av, int ac, int *i, t_fd *fd);
int					set_file(char *file, int mode);
void				check_args(int ac, int mode);
void				close_fd(t_fd fd);
int					listsize(t_cmd *lst);

#endif