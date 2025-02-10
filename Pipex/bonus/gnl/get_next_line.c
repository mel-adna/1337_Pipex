/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:35:44 by mel-adna          #+#    #+#             */
/*   Updated: 2024/12/04 08:56:55 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*up_rest(char **rest)
{
	char	*restline;
	int		index;

	index = ft_strchr(*rest, '\n');
	if (index == -1)
		return (free_str(rest), NULL);
	index++;
	restline = malloc(ft_strlen(*rest + index) + 1);
	if (!restline)
		return (free_str(rest), NULL);
	ft_strlcpy(restline, *rest + index, ft_strlen(*rest + index) + 1);
	free(*rest);
	*rest = restline;
	return (*rest);
}

char	*extract_line(char *rest)
{
	char	*line;
	int		i;
	int		index;

	index = ft_strchr(rest, '\n');
	if (index != -1)
		i = index + 1;
	else
		i = ft_strlen(rest);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, rest, i + 1);
	return (line);
}

char	*readline(int fd, char *rest)
{
	char	*buff;
	char	*temp;
	ssize_t	nread;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(rest), NULL);
	nread = read(fd, buff, BUFFER_SIZE);
	while (nread > 0)
	{
		buff[nread] = '\0';
		temp = rest;
		rest = ft_strjoin(rest, buff);
		free(temp);
		temp = NULL;
		if (!rest)
			return (free(buff), NULL);
		if (ft_strchr(buff, '\n') > -1)
			break ;
		nread = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*strline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free_str(&rest), NULL);
	rest = readline(fd, rest);
	if (!rest || *rest == '\0')
		return (free_str(&rest), NULL);
	strline = extract_line(rest);
	if (!strline)
		return (free_str(&rest), NULL);
	if (!up_rest(&rest))
		return (free_str(&rest), strline);
	return (strline);
}
