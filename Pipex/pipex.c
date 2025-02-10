/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:33:15 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 11:10:55 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		free_arr((*cmds)->str);
		free(*cmds);
		*cmds = tmp;
	}
}

void	add_cmds(t_cmd **cmd, char *av)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (!cmd || !av)
		return ;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->str = parse_arg(av);
	new->next = NULL;
	if (!*cmd)
		*cmd = new;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	set_file(char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	t_fd	fd;
	t_cmd	*cmds;
	int		i;

	i = 2;
	cmds = NULL;
	if (ac == 5)
	{
		fd.in = set_file(av[1], 0);
		fd.out = set_file(av[ac - 1], 1);
		while (i < ac -1)
			add_cmds(&cmds, av[i++]);
		if (!cmds)
			return (1);
		ft_pipex(cmds, fd, env);
		free_cmds(&cmds);
	}
	else
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
}
