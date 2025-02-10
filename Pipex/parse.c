/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:02:29 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 15:03:13 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_empty_or_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (!str[i]);
}

char	*check_quote(char *str, int *i)
{
	int		start;
	char	*word;

	if (str[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		word = ft_substr(str, start, *i - start);
		if (str[*i])
			(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && str[*i] != ' ')
			(*i)++;
		word = ft_substr(str, start, *i - start);
	}
	return (word);
}

char	**parse_arg(char *str)
{
	char	**args;
	int		i;
	int		count;

	if (!str || is_empty_or_spaces(str))
		return (ft_putstr_fd("Error: empty command\n", 2), NULL);
	args = malloc(sizeof(char *) * 42);
	if (!args)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		args[count] = check_quote(str, &i);
		if (!args[count])
			return (free_paths(args));
		count++;
	}
	args[count] = NULL;
	return (args);
}
