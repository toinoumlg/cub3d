/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:26:41 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 13:14:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
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

static int	is_walkable(char **map, t_vector2 size, float x, float y)
{
	const double	padding = 0.1;
	t_vector2		min;
	t_vector2		max;

	if (x - padding < 0 || y - padding < 0 || x + padding >= size.x || y
		+ padding >= size.y)
		return (0);
	min.x = (int)(x - padding);
	min.y = (int)(y - padding);
	max.x = (int)(x + padding);
	max.y = (int)(y + padding);
	return (map[min.y][min.x] == '0' && map[min.y][max.x] == '0'
		&& map[max.y][min.x] == '0' && map[max.y][max.x] == '0');
}

void	move(t_double2 *dir, t_cub3d *data, int direction)
{
	t_double2	new_pos;
	t_double2	*old_pos;

	old_pos = &data->player.pos;
	new_pos.x = old_pos->x + dir->x * (direction * data->timer.delta_time);
	new_pos.y = old_pos->y + dir->y * (direction * data->timer.delta_time);
	if (is_walkable(data->minimap.array, data->minimap.size, old_pos->x,
			new_pos.y))
		old_pos->y = new_pos.y;
	if (is_walkable(data->minimap.array, data->minimap.size, new_pos.x,
			old_pos->y))
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
	data->minimap.offset.x = data->player.pos.x
		- data->minimap.visible_square.x;
	data->minimap.offset.y = data->player.pos.y
		- data->minimap.visible_square.y;
}
