/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:59:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:30:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"

void	flood_fill(int x, int y, t_vector2 size, t_cub3d *data)
{
	int	**map;

	map = data->minimap.array;
	if (x < 0 || x >= size.x || y < 0 || y >= size.y || map[y][x] == -1)
		exit_error("Map contains hole(s)", data);
	if (map[y][x] != 0)
		return ;
	map[y][x] = 2;
	flood_fill(x + 1, y, size, data);
	flood_fill(x - 1, y, size, data);
	flood_fill(x, y + 1, size, data);
	flood_fill(x, y - 1, size, data);
	return ;
}

void	restore_map(int **map, t_vector2 size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (map[y][x] == 2)
				map[y][x] = 0;
			x++;
		}
		y++;
	}
}
