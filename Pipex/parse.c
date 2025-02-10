/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:55:58 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/10 10:56:11 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_quote(char *str, int *i, int *start, int mode)
{
	if (mode == 1)
	{
		(*i)++;
		*start = *i;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
			return (ft_substr(str, *start, *i++ - *start));
		return (NULL);
	}
	else
	{
		while (str[*i] && str[*i] != ' ')
			(*i)++;
		return (ft_substr(str, *start, *i - *start));
	}
}

char	**parse_arg(char *str)
{
	char	**args;
	int		start;
	int		count;
	int		i;

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
		start = i;
		if (str[i] == '\'')
			args[count] = check_quote(str, &i, &start, 1);
		else
			args[count] = check_quote(str, &i, &start, 0);
		count++;
	}
	args[count] = NULL;
	return (args);
}
