/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:00:08 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 11:00:35 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	change_fd(int fd, int oldfd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Dup2 failed");
	close(oldfd);
}
