/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:26:41 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:33:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	rotate(t_double2 *dir, t_double2 *plane, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dir->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = old_dir_x * sin(speed) + dir->y * cos(speed);
	old_plane_x = plane->x;
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = old_plane_x * sin(speed) + plane->y * cos(speed);
}

static int	is_walkable(int **map, t_vector2 map_size, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_size.x || y >= map_size.y)
		return (0);
	return (map[y][x] == 0);
}

void	move(t_double2 *dir, t_cub3d *data, float speed)
{
	t_double2	new_pos;
	t_double2	*old_pos;

	old_pos = &data->player.pos;
	new_pos.x = old_pos->x + dir->x * speed;
	new_pos.y = old_pos->y + dir->y * speed;
	if (is_walkable(data->map, data->map_size, (int)old_pos->x, (int)new_pos.y))
		old_pos->y = new_pos.y;
	if (is_walkable(data->map, data->map_size, (int)new_pos.x, (int)old_pos->y))
		old_pos->x = new_pos.x;
}
