/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:50:31 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:30:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "mem.h"
#include "str.h"
#include <stdio.h>
#include <string.h>

int	map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

void	get_size(char **config, t_vector2 *size)
{
	int	tmp;

	while (*config)
	{
		if (!map_line(*config) || **config == '\n')
			break ;
		tmp = ft_strlen_with_tab(*config);
		if (tmp > size->x)
			size->x = tmp;
		size->y++;
		config++;
	}
}

void	copy_map_row(char *line, int *map_row, t_cub3d *data)
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
			exit_error("Invalid character in map", data);
		line++;
	}
}

void	check_remaining_lines(char **config, t_cub3d *data)
{
	int		i;
	char	*error_str;

	error_str = "Config files has non white-space character after map";
	while (*config)
	{
		i = 0;
		while ((*config)[i])
		{
			if ((*config)[i] != '\n' && (*config)[i] != ' '
				&& (*config)[i] != '\t')
				exit_error(error_str, data);
			i++;
		}
		config++;
	}
}

void	copy_map(char **config, t_cub3d *data)
{
	int	i;

	i = 0;
	get_size(config, &data->minimap.size);
	if (data->minimap.size.x < 3 || data->minimap.size.y < 3)
		exit_error("Map is too small", data);
	alloc_map(data);
	while (*config)
	{
		if (**config == '\n')
			break ;
		copy_map_row(*config++, data->minimap.array[i++], data);
	}
	check_remaining_lines(config, data);
}

void	load_map(char **config, t_cub3d *data)
{
	while (*config)
	{
		if (map_line(*config))
			return (copy_map(config, data));
		config++;
	}
	exit_error("No map found in config", data);
}
