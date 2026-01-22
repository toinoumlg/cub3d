/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:03:13 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/22 11:55:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	set_dir(int direction, t_double2 *dir, t_double2 *plane)
{
	double	pi;

	pi = acos(-1.0);
	if (direction == 'S')
		return (rotate(dir, plane, 3 * pi / 2.0, 1));
	else if (direction == 'N')
		return (rotate(dir, plane, pi / 2.0, 1));
	else if (direction == 'E')
		return (rotate(dir, plane, pi, 1));
	else
		return ;
}

static t_vector2	find_player(int **map, t_vector2 map_size, t_cub3d *data)
{
	t_vector2	new;

	new = set_vector2(0, 0);
	while (new.y < map_size.y)
	{
		new.x = 0;
		while (new.x < map_size.x)
		{
			if (map[new.y][new.x] == 'N' || map[new.y][new.x] == 'E'
				|| map[new.y][new.x] == 'S' || map[new.y][new.x] == 'W')
				return (new);
			new.x++;
		}
		new.y++;
	}
	exit_error("No player position on map", data);
	return (new);
}

void	set_player(int **map, t_vector2 map_size, t_double2 *plane,
		t_cub3d *data)
{
	t_vector2	coords;

	coords = find_player(map, map_size, data);
	data->player.dir = set_double2(-1.0, 0.0);
	set_dir(map[coords.y][coords.x], &data->player.dir, plane);
	data->player.pos = set_double2(coords.x + 0.5, coords.y + 0.5);
	map[coords.y][coords.x] = 0;
}

void	parse_config(t_cub3d *data)
{
	// fix texture can be with S or SO
	data->ceiling = set_color_from_config("C ", data->config, data);
	data->floor = set_color_from_config("F ", data->config, data);
	data->textures[0] = init_texture_from_config("SO ", data);
	data->textures[1] = init_texture_from_config("WE ", data);
	data->textures[2] = init_texture_from_config("NO ", data);
	data->textures[3] = init_texture_from_config("EA ", data);
	load_map(data->config, data);
	data->plane = set_double2(0.0, 0.66);
	set_player(data->map, data->map_size, &data->plane, data);
	flood_fill(data->player.pos.x, data->player.pos.y, data->map_size, data);
	restore_map(data->map, data->map_size);
}
