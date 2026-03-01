/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:18:56 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 22:49:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize ray values for the current screen column.
 *
 * Computes ray direction, camera position, delta distances
 * and starting map cell.
 *
 * @param x Current screen column.
 * @param ray Pointer to raycast structure.
 * @param player Pointer to player data.
 */
static void	init_raycast_info(int x, t_raycast *ray, t_player *player)
{
	float	cam_x;

	cam_x = 2.0 * x / (float)WIN_WIDTH - 1.0;
	if (player->inputs.zoom)
		cam_x = cam_x / 2.0;
	ray->dir.x = player->dir.x + player->plane.x * cam_x;
	ray->dir.y = player->dir.y + player->plane.y * cam_x;
	ray->deltadist.x = fabs(1.0 / ray->dir.x);
	ray->deltadist.y = fabs(1.0 / ray->dir.y);
}

/**
 * @brief Initialize DDA stepping direction and side distances.
 *
 * Determines ray step direction and initial distance to the
 * first grid boundary.
 *
 * @param ray Pointer to raycast structure.
 * @param player Pointer to player data.
 */
static void	init_dda_step(t_double2 ray_pos, t_vector2 *step, t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		step->x = -1;
		ray->sidedist.x = (ray_pos.x - (int)ray_pos.x) * ray->deltadist.x;
	}
	else
	{
		step->x = 1;
		ray->sidedist.x = ((int)ray_pos.x + 1.0 - ray_pos.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		step->y = -1;
		ray->sidedist.y = (ray_pos.y - (int)ray_pos.y) * ray->deltadist.y;
	}
	else
	{
		step->y = 1;
		ray->sidedist.y = ((int)ray_pos.y + 1.0 - ray_pos.y) * ray->deltadist.y;
	}
}

int	inside_map(t_double2 ray_pos, t_vector2 size)
{
	return ((int)ray_pos.x > 0 && (int)ray_pos.x < size.x && (int)ray_pos.y > 0
		&& (int)ray_pos.y < size.y);
}
/**
 * @brief Perform the DDA (Digital Differential Analyzer)
 * algorithm to detect wall collision.
 *
 * Steps through the map grid until a wall is hit or
 * bounds are exceeded.
 *
 * @param engine Pointer to engine data.
 * @param ray Pointer to raycast structure.
 */
static void	execute_dda(char **map, t_double2 ray_pos, t_raycast *ray,
		t_vector2 size)
{
	t_vector2	step;

	init_dda_step(ray_pos, &step, ray);
	while (1)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray_pos.x += step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray_pos.y += step.y;
			ray->side = 1;
		}
		if (!inside_map(ray_pos, size)
			|| map[(int)ray_pos.y][(int)ray_pos.x] != '0')
			break ;
	}
}

/**
 * @brief Compute wall distance and vertical line projection.
 *
 * Calculates wall distance, line height, draw range
 * and texture coordinate.
 *
 * @param ray Pointer to raycast structure.
 * @param engine Pointer to engine data.
 * @param player Pointer to player data.
 */
static void	compute_wall_projection(t_raycast *ray)
{
	if (!ray->side)
		ray->wall_dist = ray->sidedist.x - ray->deltadist.x;
	else
		ray->wall_dist = ray->sidedist.y - ray->deltadist.y;
	ray->line_height = WIN_HEIGHT / ray->wall_dist;
	ray->draw_start = WIN_HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	find_wall_dir(t_raycast *ray)
{
	if (!ray->side && ray->dir.x > 0)
		ray->wall_dir = WEST;
	else if (!ray->side)
		ray->wall_dir = EAST;
	else if (ray->dir.y > 0)
		ray->wall_dir = NORTH;
	else
		ray->wall_dir = SOUTH;
}

void	compute_texture_coords(t_raycast *ray, t_double2 *player_pos,
		t_image *textures)
{
	double	wall_x;

	find_wall_dir(ray);
	if (!ray->side)
		wall_x = player_pos->y + ray->wall_dist * ray->dir.y;
	else
		wall_x = player_pos->x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	ray->texture_coord.x = wall_x * textures[ray->wall_dir].w;
	ray->step = 1.0 * textures[ray->wall_dir].h / ray->line_height;
	ray->texture_coord.y = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height
			/ 2) * ray->step;
	if ((!ray->side && ray->dir.x > 0) || (ray->side && ray->dir.y < 0))
		ray->texture_coord.x = textures[ray->wall_dir].w - ray->texture_coord.x
			- 1;
}

/**
 * @brief Perform raycasting for the entire screen.
 *
 * Casts one ray per screen column and updates texture rendering.
 *
 * @param player Pointer to player data.
 * @param engine Pointer to engine data.
 * @return SUCCESS on completion.
 */
void	perform_raycasting(t_player *player, t_engine *engine)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_raycast_info(x, &engine->ray, player);
		execute_dda(engine->map, engine->player.pos, &engine->ray,
			engine->map_size);
		compute_wall_projection(&engine->ray);
		compute_texture_coords(&engine->ray, &player->pos, engine->textures);
		draw_vertical_line(x++, engine->buffer.addr, &engine->ray,
			&engine->textures[engine->ray.wall_dir]);
	}
}
