/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:26:38 by amalangu          #+#    #+#             */
/*   Updated: 2025/12/15 13:18:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pick_color(int value, int side)
{
	int	color;

	color = create_trgb(0, 255, 255, 255);
	if (value == 0)
		color = create_trgb(0, 255, 255, 0);
	if (value == 1)
		color = create_trgb(0, 255, 0, 0);
	if (value == 2)
		color = create_trgb(0, 0, 255, 0);
	if (value == 3)
		color = create_trgb(0, 0, 0, 255);
	if (value == 4)
		color = create_trgb(0, 255, 255, 255);
	if (side)
		color = (color & 0xFF000000) | (((color & 0x00FEFEFE) >> 1));
	return (color);
}

void	check_ray_dir(t_raycaster *rc, t_cub3d *data)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->s_dist.x = (data->player.pos.x - rc->map_pos.x) * rc->d_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->s_dist.x = (rc->map_pos.x + 1 - data->player.pos.x) * rc->d_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->s_dist.y = (data->player.pos.y - rc->map_pos.y) * rc->d_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->s_dist.y = (rc->map_pos.y + 1 - data->player.pos.y) * rc->d_dist.y;
	}
}

void	generate_line(t_raycaster *rc, t_cub3d *data)
{
	while (rc->hit == 0)
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
		if (data->map[rc->map_pos.y][rc->map_pos.x] > 0)
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perp_dist = (rc->s_dist.x - rc->d_dist.x);
	else
		rc->perp_dist = (rc->s_dist.y - rc->d_dist.y);
}

void	init_raycast(t_raycaster *rc, t_cub3d *data)
{
	rc->map_pos.x = (int)data->player.pos.x;
	rc->map_pos.y = (int)data->player.pos.y;
	rc->hit = 0;
	rc->camera.x = 2.0 * rc->x / (double)WINDOW_WIDTH - 1.0;
	rc->ray_dir.x = data->player.dir.x + data->plane.x * rc->camera.x;
	rc->ray_dir.y = data->player.dir.y + data->plane.y * rc->camera.x;
	if (rc->ray_dir.x == 0.0)
		rc->ray_dir.x = 1e-9;
	if (rc->ray_dir.y == 0.0)
		rc->ray_dir.y = 1e-9;
	rc->d_dist.x = ft_abs(1 / rc->ray_dir.x);
	rc->d_dist.y = ft_abs(1 / rc->ray_dir.y);
}

t_vector2	set_draw_limit(t_raycaster rc)
{
	int			line_height;
	t_vector2	draw_limit;

	line_height = (int)(WINDOW_HEIGHT / rc.perp_dist);
	draw_limit.x = -line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (draw_limit.x < 0)
		draw_limit.x = 0;
	draw_limit.y = line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (draw_limit.y >= (int)WINDOW_HEIGHT)
		draw_limit.y = (int)WINDOW_HEIGHT - 1;
	return (draw_limit);
}

void	raycast(t_cub3d *data)
{
	t_raycaster	rc;
	t_vector2	draw_limit;
	int			color;

	rc.x = 0;
	while (rc.x < (int)WINDOW_WIDTH)
	{
		init_raycast(&rc, data);
		check_ray_dir(&rc, data);
		generate_line(&rc, data);
		draw_limit = set_draw_limit(rc);
		color = pick_color(data->map[rc.map_pos.y][rc.map_pos.x], rc.side);
		draw_vert_line(rc.x, draw_limit, color, data);
		rc.x++;
	}
}
