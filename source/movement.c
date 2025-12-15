/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:26:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/12/15 13:16:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	move_fwd(t_double2 *dir, t_double2 *pos, int **map, t_double2 map_size)
{
	t_double2	new_pos;

	new_pos.x = pos->x + dir->x * SPEED;
	new_pos.y = pos->y + dir->y * SPEED;
	if (is_walkable(map, map_size, (int)new_pos.x, (int)pos->y))
		pos->x = new_pos.x;
	if (is_walkable(map, map_size, (int)pos->x, (int)new_pos.y))
		pos->y = new_pos.y;
}

void	move_bwd(t_double2 *dir, t_double2 *pos, int **map, t_double2 map_size)
{
	t_double2	new_pos;

	new_pos.x = pos->x + dir->x * -SPEED;
	new_pos.y = pos->y + dir->y * -SPEED;
	if (is_walkable(map, map_size, (int)new_pos.x, (int)pos->y))
		pos->x = new_pos.x;
	if (is_walkable(map, map_size, (int)pos->x, (int)new_pos.y))
		pos->y = new_pos.y;
}

void	move_left(t_double2 *dir, t_double2 *pos, int **map, t_double2 map_size)
{
	t_double2	new_pos;
	t_double2	strafe;

	strafe.x = -dir->y;
	strafe.y = dir->x;
	new_pos.x = pos->x + strafe.x * SPEED;
	new_pos.y = pos->y + strafe.y * SPEED;
	if (is_walkable(map, map_size, (int)new_pos.x, (int)pos->y))
		pos->x = new_pos.x;
	if (is_walkable(map, map_size, (int)pos->x, (int)new_pos.y))
		pos->y = new_pos.y;
}

void	move_right(t_double2 *dir, t_double2 *pos, int **map,
		t_double2 map_size)
{
	t_double2	new_pos;
	t_double2	strafe;

	strafe.x = dir->y;
	strafe.y = -dir->x;
	new_pos.x = pos->x + strafe.x * SPEED;
	new_pos.y = pos->y + strafe.y * SPEED;
	if (is_walkable(map, map_size, (int)new_pos.x, (int)pos->y))
		pos->x = new_pos.x;
	if (is_walkable(map, map_size, (int)pos->x, (int)new_pos.y))
		pos->y = new_pos.y;
}
