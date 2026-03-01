/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:55:07 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 22:28:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init_direction.c
 * @brief Initializes the player's direction and camera plane
 * vectors based on the starting orientation.
 *
 * This file contains functions to set the player's
 * initial direction and camera plane
 * vectors according to the direction character ('N', 'S', 'E', 'W')
 * specified in the player structure.
 * These vectors are essential for the raycasting algorithm to render
 * the 3D view correctly.
 */
#include "cub3d.h"

#define FOV 70

static double	get_plane_lenght(double pi)
{
	float	deg_to_rad;

	deg_to_rad = FOV * pi / 180.0;
	return (tanf(deg_to_rad / 2.0));
}

int	is_player_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static t_double2	find_player(char **map, t_engine *data)
{
	int			x;
	int			y;
	t_double2	pos;

	ft_memset(&pos, 0, sizeof(t_double2));
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_pos(map[y][x]))
			{
				if (pos.x || pos.y)
					exit_free(data, NULL, "Multiple starting position",
						FAILURE);
				pos.x = x;
				pos.y = y;
			}
			x++;
		}
		y++;
	}
	if (!pos.x || !pos.y)
		exit_free(data, NULL, "No starting position", FAILURE);
	return (pos);
}

void	set_player_dir(char **map, t_player *player, double pi)
{
	char	direction;

	direction = map[(int)player->pos.y][(int)player->pos.x];
	if (direction == 'W')
		return (rotate(&player->dir, &player->plane, 3 * pi / 2.0));
	else if (direction == 'E')
		return (rotate(&player->dir, &player->plane, pi / 2.0));
	else if (direction == 'S')
		return (rotate(&player->dir, &player->plane, pi));
	else
		return ;
}

/**
 * @brief Initialize the player's direction and camera plane vectors.
 *
 * Based on the direction character stored in the player structure
 * ('N', 'S', 'E', or 'W'), this function initializes the direction
 * vector and camera plane required for raycasting.
 *
 * @param engine Pointer to the main engine structure.
 */
void	set_player(t_engine *data)
{
	double	plane_lenght;
	double	pi;

	pi = acos(-1.0);
	plane_lenght = get_plane_lenght(pi);
	data->player.pos = find_player(data->map, data);
	data->player.dir.y = -1.0;
	data->player.plane.x = plane_lenght;
	set_player_dir(data->map, &data->player, pi);
	data->map[(int)data->player.pos.y][(int)data->player.pos.x] = '0';
	data->player.pos.y += 0.5;
	data->player.pos.x += 0.5;
}
