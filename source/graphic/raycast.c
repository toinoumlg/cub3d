/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:26:38 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:30:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

void	init_raycast(t_raycaster *rc, t_player *player, int x)
{
	float	cam_x;

	cam_x = 2.0 * x / WINDOW_WIDTH - 1.0;
	if (player->inputs.zoom)
		cam_x = cam_x / 2.0;
	rc->ray_dir.x = player->dir.x + player->plane.x * cam_x;
	rc->ray_dir.y = player->dir.y + player->plane.y * cam_x;
	rc->d_dist.x = ft_abs(1 / rc->ray_dir.x);
	rc->d_dist.y = ft_abs(1 / rc->ray_dir.y);
}

static void	set_draw_limit(t_raycaster *rc, t_player *player)
{
	rc->line_height = (WINDOW_HEIGHT / rc->perp_dist);
	if (player->inputs.zoom)
		rc->line_height = rc->line_height * 2;
	rc->draw_limit.x = -rc->line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (rc->draw_limit.x < 0)
		rc->draw_limit.x = 0;
	rc->draw_limit.y = rc->line_height / 2 + (int)WINDOW_HEIGHT / 2;
	if (rc->draw_limit.y >= (int)WINDOW_HEIGHT)
		rc->draw_limit.y = (int)WINDOW_HEIGHT - 1;
}

t_img	*find_texture(int side, t_double2 ray_dir, t_img *textures)
{
	if (!side && ray_dir.x > 0)
		return (&textures[1]);
	else if (!side)
		return (&textures[3]);
	else if (ray_dir.y > 0)
		return (&textures[2]);
	else
		return (&textures[0]);
}

static void	process_texture_coords(t_raycaster *rc, t_double2 *player_pos,
		t_img *textures)
{
	double	wall_x;

	rc->text = find_texture(rc->side, rc->ray_dir, textures);
	if (!rc->side)
		wall_x = player_pos->y + rc->perp_dist * rc->ray_dir.y;
	else
		wall_x = player_pos->x + rc->perp_dist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	rc->text_coord.x = wall_x * rc->text->w;
	rc->step = 1.0 * rc->text->w / rc->line_height;
	rc->text_coord.y = (rc->draw_limit.x - WINDOW_HEIGHT / 2 + rc->line_height
			/ 2) * rc->step;
	if ((!rc->side && rc->ray_dir.x > 0) || (rc->side && rc->ray_dir.y < 0))
		rc->text_coord.x = rc->text->w - rc->text_coord.x - 1;
}

void	raycast(t_minimap *minimap, t_player *player, t_img *textures,
		t_pxl *buffer)
{
	int			x;
	t_raycaster	rc;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_raycast(&rc, player, x);
		find_perp_dist(minimap->array, player->pos, &rc);
		set_draw_limit(&rc, player);
		draw_lines_on_map(&rc, minimap, &player->pos);
		process_texture_coords(&rc, &player->pos, textures);
		draw_vertical_line(x++, buffer, &rc);
	}
}
