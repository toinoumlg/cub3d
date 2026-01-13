/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:59:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:34:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"

void	flood_fill(int x, int y, t_vector2 map_size, t_cub3d *data)
{
	int	**map;

	map = data->map;
	if (x < 0 || x >= map_size.x || y < 0 || y > map_size.y || map[y][x] == -1)
		exit_error("Map contains hole(s)", data);
	if (map[y][x] != 0)
		return ;
	map[y][x] = 2;
	flood_fill(x + 1, y, map_size, data);
	flood_fill(x - 1, y, map_size, data);
	flood_fill(x, y + 1, map_size, data);
	flood_fill(x, y - 1, map_size, data);
	return ;
}

void	restore_map(int **map, t_vector2 map_size)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == 2)
				map[y][x] = 0;
			x++;
		}
		y++;
	}
}
