/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:03:13 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 14:25:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	set_dir(int direction, t_player *player, double pi)
{
	if (direction == 'W')
		return (rotate(&player->dir, &player->plane, 3 * pi / 2.0, 1));
	else if (direction == 'E')
		return (rotate(&player->dir, &player->plane, pi / 2.0, 1));
	else if (direction == 'S')
		return (rotate(&player->dir, &player->plane, pi, 1));
	else
		return ;
}

static t_vector2	find_player(char **map, t_vector2 size, t_cub3d *data)
{
	t_vector2	i;
	t_vector2	pos;

	pos = set_vector2(-1, -1);
	i = set_vector2(0, 0);
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			if (map[i.y][i.x] == 'N' || map[i.y][i.x] == 'E'
				|| map[i.y][i.x] == 'S' || map[i.y][i.x] == 'W')
			{
				if (pos.y > 0 || pos.x > 0)
					exit_error("Multiple starting position", data);
				pos = i;
			}
			i.x++;
		}
		i.y++;
	}
	if (pos.x < 0 || pos.y < 0)
		exit_error("No player position on map", data);
	return (pos);
}

static float	get_plane_lenght(double pi)
{
	float	deg_to_rad;

	deg_to_rad = FOV * pi / 180.0f;
	return (tanf(deg_to_rad / 2.0f));
}

void	set_player(char **map, t_vector2 size, t_cub3d *data)
{
	t_vector2	coords;
	float		plane_lenght;
	double		pi;

	pi = acos(-1.0);
	plane_lenght = get_plane_lenght(pi);
	coords = find_player(map, size, data);
	data->player.dir = set_double2(0, -1.0);
	data->player.plane = set_double2(plane_lenght, 0.0);
	set_dir(map[coords.y][coords.x], &data->player, pi);
	data->player.pos = set_double2(coords.x + 0.5, coords.y + 0.5);
	map[coords.y][coords.x] = '0';
}

void	parse_config(t_cub3d *data)
{
	data->ceiling = set_color_from_config("C ", data->config, data);
	data->floor = set_color_from_config("F ", data->config, data);
	data->textures[0] = init_texture_from_config("SO ", data);
	data->textures[1] = init_texture_from_config("WE ", data);
	data->textures[2] = init_texture_from_config("NO ", data);
	data->textures[3] = init_texture_from_config("EA ", data);
	load_map(data->config, data);
	set_player(data->minimap.array, data->minimap.size, data);
	flood_fill(data->player.pos.x, data->player.pos.y, data->minimap.size,
		data);
	restore_map(data->minimap.array, data->minimap.size);
}
