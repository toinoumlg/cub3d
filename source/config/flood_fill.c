/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:59:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 10:23:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"

int	is_oob(char c)
{
	return (c == '\n' || c == ' ' || c == '\t' || c == '\n');
}

void	flood_fill(int x, int y, t_vector2 size, t_cub3d *data)
{
	char	**map;

	map = data->minimap.array;
	if (x < 0 || x >= size.x || y < 0 || y >= size.y || is_oob(map[y][x]))
		exit_error("Map contains hole(s)", data);
	if (map[y][x] != '0')
		return ;
	map[y][x] = '2';
	flood_fill(x + 1, y, size, data);
	flood_fill(x - 1, y, size, data);
	flood_fill(x, y + 1, size, data);
	flood_fill(x, y - 1, size, data);
	return ;
}

void	restore_map(char **map, t_vector2 size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (map[y][x] == '2')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}
