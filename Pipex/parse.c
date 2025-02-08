/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:33:09 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/08 13:34:50 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	skip_spaces(char *s, int *i)
{
	while (s[*i] == ' ')
		(*i)++;
}

char	*extract_quoted(char *input, int *i)
{
	int		start;
	char	*res;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
	{
		res = ft_substr(input, start, *i - start);
		(*i)++;
		return (res);
	}
	return (NULL);
}

char	*extract_word(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

char	**parse_args(char *input)
{
	char	**args;
	int		i;
	int		count;

	args = malloc(sizeof(char *) * 42);
	if (!args)
		return (NULL);
	i = 0;
	count = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '\'')
			args[count] = extract_quoted(input, &i);
		else
			args[count] = extract_word(input, &i);
		count++;
	}
	args[count] = NULL;
	return (args);
}
