/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 19:10:41 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 19:15:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include <stdbool.h>

static bool	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S'
		|| c == 'W');
}

static bool	is_whitespace(char c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == ' ');
}

char	*skip_whitespace(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

bool	is_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || is_whitespace(str[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

int	map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!is_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}
