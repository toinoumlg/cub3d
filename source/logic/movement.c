/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:26:41 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/23 23:43:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	rotate(t_double2 *dir, t_double2 *plane, float direction, double d_time)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dir->x;
	dir->x = dir->x * cos(direction * d_time) - dir->y * sin(direction
			* d_time);
	dir->y = old_dir_x * sin(direction * d_time) + dir->y * cos(direction
			* d_time);
	old_plane_x = plane->x;
	plane->x = plane->x * cos(direction * d_time) - plane->y * sin(direction
			* d_time);
	plane->y = old_plane_x * sin(direction * d_time) + plane->y * cos(direction
			* d_time);
}

static int	is_walkable(int **map, t_vector2 map_size, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_size.x || y >= map_size.y)
		return (0);
	return (map[y][x] == 0);
}

void	move(t_double2 *dir, t_cub3d *data, int direction)
{
	t_double2	new_pos;
	t_double2	*old_pos;

	old_pos = &data->player.pos;
	new_pos.x = old_pos->x + dir->x * (direction * data->timer.delta_time);
	new_pos.y = old_pos->y + dir->y * (direction * data->timer.delta_time);
	if (is_walkable(data->map, data->map_size, (int)old_pos->x, (int)new_pos.y))
		old_pos->y = new_pos.y;
	if (is_walkable(data->map, data->map_size, (int)new_pos.x, (int)old_pos->y))
		old_pos->x = new_pos.x;
}

void	apply_motion(t_cub3d *data)
{
	if (data->player.inputs.right)
		rotate(&data->player.dir, &data->player.plane, 2,
			data->timer.delta_time);
	if (data->player.inputs.left)
		rotate(&data->player.dir, &data->player.plane, -2,
			data->timer.delta_time);
	if (data->player.inputs.w)
		move(&data->player.dir, data, 2);
	if (data->player.inputs.s)
		move(&data->player.dir, data, -2);
	if (data->player.inputs.d)
		move(&data->player.plane, data, 2);
	if (data->player.inputs.a)
		move(&data->player.plane, data, -2);
}
