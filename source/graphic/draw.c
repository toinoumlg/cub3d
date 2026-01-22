/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:43 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/21 10:54:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include "struct.h"

/// @brief clear the image with 2 color (floor/ceiling)
void	clear_image(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			pxl_put(data->buffer, x++, y, data->floor);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			pxl_put(data->buffer, x++, y, data->ceiling);
		y++;
	}
}

static void	process_texture_coords(t_raycaster *rc, int width,
		t_double2 player_pos)
{
	if (!rc->side)
		rc->wall_x = player_pos.y + rc->perp_dist * rc->ray_dir.y;
	else
		rc->wall_x = player_pos.x + rc->perp_dist * rc->ray_dir.x;
	rc->wall_x -= floor(rc->wall_x);
	rc->texture.x = rc->wall_x * (double)width;
	if (!rc->side && rc->ray_dir.x > 0)
		rc->texture.x = width - rc->texture.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->texture.x = width - rc->texture.x - 1;
	rc->texture_step = 1.0 * width / rc->line_height;
	rc->texture.y = (rc->draw_limit.x - WINDOW_HEIGHT / 2 + rc->line_height / 2)
		* rc->texture_step;
}

void	draw_vertical_line(t_raycaster rc, t_cub3d *data)
{
	int	color;

	process_texture_coords(&rc, data->textures->w, data->player.pos);
	while (rc.draw_limit.x < rc.draw_limit.y)
	{
		rc.texture.y += rc.texture_step;
		color = get_texture_pixel_color(data->textures[get_texture_index(rc)],
				rc.texture.x, rc.texture.y);
		pxl_put(data->buffer, rc.x, rc.draw_limit.x++, color);
	}
}
