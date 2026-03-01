/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:49:24 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 22:24:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_validation.c
 * @brief Functions to validate the map structure and
 * player position for the cub3D engine.
 */

#include "cub3d.h"

void	flood_fill(int x, int y, char **map, t_engine *data)
{
	if (x < 0 || x >= data->map_size.x || y < 0 || y >= data->map_size.y
		|| !is_blank(map[y][x]))
		exit_free(data, NULL, "Map contains hole(s)", FAILURE);
	if (map[y][x] != '0')
		return ;
	map[y][x] = '2';
	flood_fill(x + 1, y, map, data);
	flood_fill(x - 1, y, map, data);
	flood_fill(x, y + 1, map, data);
	flood_fill(x, y - 1, map, data);
}

void	restore_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '2')
				map[y][x] = '0';
			if (map[y][x] != '0' && map[y][x] != '1')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
}

/**
 * @brief Perform full map validation.
 *
 * This function validates:
 *  - Map existence
 *  - Wall enclosure
 *  - Minimum size
 *  - Valid characters
 *  - Player position
 *  - Map placement in file
 *
 * @param engine Pointer to the main engine structure.
 * @param map 2D array representing the map.
 * @return SUCCESS if the map is valid, FAILURE otherwise.
 */
void	validate_map(t_engine *data, char **map)
{
	flood_fill(data->player.pos.x, data->player.pos.y, data->map, data);
	restore_map(map);
}
