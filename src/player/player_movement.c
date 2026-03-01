/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:14:28 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:16:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file player_movement.c
 * @brief Handles player movement and rotation based on input state.
 *
 * This file contains functions to move the player forward, backward, and
 * strafe left/right based on the player's current direction. It also includes
 * the main function to update the player's movement and rotation state each
 * frame based on the input received.
 */

#include "cub3d.h"

static int	is_walkable(char **map, t_vector2 size, double x, double y)
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

void	move(t_double2 *dir, t_engine *data, double direction)
{
	t_double2	new_pos;
	t_double2	*old_pos;

	old_pos = &data->player.pos;
	new_pos.x = old_pos->x + dir->x * direction;
	new_pos.y = old_pos->y + dir->y * direction;
	if (is_walkable(data->map, data->map_size, old_pos->x, new_pos.y))
		old_pos->y = new_pos.y;
	if (is_walkable(data->map, data->map_size, new_pos.x, old_pos->y))
		old_pos->x = new_pos.x;
}

void	rotate(t_double2 *dir, t_double2 *plane, double direction)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dir->x;
	dir->x = dir->x * cos(direction) - dir->y * sin(direction);
	dir->y = old_dir_x * sin(direction) + dir->y * cos(direction);
	old_plane_x = plane->x;
	plane->x = plane->x * cos(direction) - plane->y * sin(direction);
	plane->y = old_plane_x * sin(direction) + plane->y * cos(direction);
}

/**
 * @brief Updates player movement and rotation based on input state.
 *
 * @param engine Pointer to the main engine structure.
 * @return Number of movement actions performed.
 */
int	consume_player_movement(t_engine *data)
{
	t_input	input;
	double	d_rot;
	double	d_move;

	d_rot = ROTSPEED * data->timer.delta_time;
	d_move = MOVESPEED * data->timer.delta_time;
	input = data->player.inputs;
	if (input.right)
		rotate(&data->player.dir, &data->player.plane, d_rot);
	if (input.left)
		rotate(&data->player.dir, &data->player.plane, -d_rot);
	if (input.w)
		move(&data->player.dir, data, d_move);
	if (input.s)
		move(&data->player.dir, data, -d_move);
	if (input.d)
		move(&data->player.plane, data, d_move);
	if (input.a)
		move(&data->player.plane, data, -d_move);
	data->minimap.offset.x = data->player.pos.x - data->minimap.visible_square;
	data->minimap.offset.y = data->player.pos.y - data->minimap.visible_square;
	return (0);
}
