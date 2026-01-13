/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:26:38 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:42:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

static void	check_ray_dir(t_raycaster *rc, t_double2 player_pos)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->s_dist.x = (player_pos.x - rc->map_pos.x) * rc->d_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->s_dist.x = (rc->map_pos.x + 1 - player_pos.x) * rc->d_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->s_dist.y = (player_pos.y - rc->map_pos.y) * rc->d_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->s_dist.y = (rc->map_pos.y + 1 - player_pos.y) * rc->d_dist.y;
	}
}

static void	generate_line(t_raycaster *rc, int **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->s_dist.x < rc->s_dist.y)
		{
			rc->s_dist.x += rc->d_dist.x;
			rc->map_pos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->s_dist.y += rc->d_dist.y;
			rc->map_pos.y += rc->step.y;
			rc->side = 1;
		}
		if (map[rc->map_pos.y][rc->map_pos.x] > 0)
			hit = 1;
	}
	if (rc->side == 0)
		rc->perp_dist = (rc->s_dist.x - rc->d_dist.x);
	else
		rc->perp_dist = (rc->s_dist.y - rc->d_dist.y);
}

static void	init_raycast(t_raycaster *rc, t_player player, t_double2 plane)
{
	rc->map_pos.x = (int)player.pos.x;
	rc->map_pos.y = (int)player.pos.y;
	rc->camera.x = 2.0 * rc->x / (double)WINDOW_WIDTH - 1.0;
	rc->ray_dir.x = player.dir.x + plane.x * rc->camera.x;
	rc->ray_dir.y = player.dir.y + plane.y * rc->camera.x;
	if (rc->ray_dir.x == 0.0)
		rc->ray_dir.x = 1e-9;
	if (rc->ray_dir.y == 0.0)
		rc->ray_dir.y = 1e-9;
	rc->d_dist.x = ft_abs(1 / rc->ray_dir.x);
	rc->d_dist.y = ft_abs(1 / rc->ray_dir.y);
}

static void	set_draw_limit(double perp_dist, int *line_height,
		t_vector2 *draw_limit)
{
	*line_height = (int)(WINDOW_HEIGHT / perp_dist);
	draw_limit->x = -*line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (draw_limit->x < 0)
		draw_limit->x = 0;
	draw_limit->y = *line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (draw_limit->y >= (int)WINDOW_HEIGHT)
		draw_limit->y = (int)WINDOW_HEIGHT - 1;
}

void	raycast(t_cub3d *data)
{
	t_raycaster	rc;

	rc.x = 0;
	while (rc.x < (int)WINDOW_WIDTH)
	{
		init_raycast(&rc, data->player, data->plane);
		check_ray_dir(&rc, data->player.pos);
		generate_line(&rc, data->map);
		set_draw_limit(rc.perp_dist, &rc.line_height, &rc.draw_limit);
		draw_vertical_line(rc, data);
		rc.x++;
	}
}
