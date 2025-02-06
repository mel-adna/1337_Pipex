#include "pipex.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_cmd_add(t_cmd **list, char *argv)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (!list || !argv)
		return ;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->str = ft_split(argv, ' ');
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	set_file(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error");
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv, char **env)
{
	t_fd	fd;
	t_cmd	*cmds;
	int		i;

	i = 2;
	cmds = NULL;
	if (argc == 5)
	{
		fd.in = set_file(argv[1], 1);
		fd.out = set_file(argv[argc - 1], 2);
		while (i < argc - 1)
			ft_cmd_add(&cmds, argv[i++]);
		ft_pipex(cmds, &fd, env);
		free_cmds(cmds);
	}
	else
	{
		ft_putendl_fd("Use: ./pipex infile cmd1 cmd2 outfile", 1);
		exit(1);
	}
}
