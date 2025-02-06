# include "pipex.h"

int main(int ac, char **av, char **env)
{
	int i;
	char **paths;
	
	i = 0;
	ac = 0;
	av = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
}