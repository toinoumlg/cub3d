/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:50:31 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:55:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "mem.h"
#include "str.h"
#include <stdio.h>
#include <string.h>

char	*check_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'W')
			return (NULL);
		i++;
	}
	return (line);
}

void	get_map_size(char **config, t_vector2 *map_size)
{
	int	tmp;

	while (*config)
	{
		if (!check_map_line(*config))
			break ;
		tmp = ft_strlen_with_tab(*config);
		if (tmp > map_size->x)
			map_size->x = tmp;
		map_size->y++;
		config++;
	}
}

void	copy_map_row(char *line, int *map_row)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == '\t')
			i += 4;
		else if (*line == '1' || *line == '0')
			map_row[i++] = *line - '0';
		else if (*line == 'N' || *line == 'E' || *line == 'S' || *line == 'W')
			map_row[i++] = *line;
		else if (*line == ' ')
			i++;
		else
			return ;
		line++;
	}
}

void	copy_map(char **config, t_cub3d *data)
{
	int	i;

	i = 0;
	get_map_size(config, &data->map_size);
	if (data->map_size.x < 3 || data->map_size.y < 3)
		exit_error("Map is too small", data);
	alloc_map(data);
	while (*config)
		copy_map_row(*config++, data->map[i++]);
}

void	load_map(char **config, t_cub3d *data)
{
	char	*line;

	while (*config)
	{
		line = check_map_line(*config);
		if (line)
			return (copy_map(config, data));
		config++;
	}
	exit_error("No map found in config", data);
}
