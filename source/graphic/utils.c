/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:29:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 13:23:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

t_pxl	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char[4]){b, g, r, 0});
}

void	set_minimap_max_value(t_vector2 *hit_minimap, t_minimap *minimap)
{
	if (hit_minimap->x < 0)
		hit_minimap->x = 0;
	if (hit_minimap->x >= minimap->buffer.w)
		hit_minimap->x = minimap->buffer.w - 1;
	if (hit_minimap->y < 0)
		hit_minimap->y = 0;
	if (hit_minimap->y >= minimap->buffer.h)
		hit_minimap->y = minimap->buffer.h - 1;
}

t_vector2	get_hit_pos_on_minimap(t_raycaster *rc,
		t_double2 *player_pos, t_minimap *minimap)
{
	t_double2	hit_map;
	t_vector2	hit_minimap;

	hit_map.x = player_pos->x + rc->perp_dist * rc->ray_dir.x;
	hit_map.y = player_pos->y + rc->perp_dist * rc->ray_dir.y;
	hit_minimap.x = (hit_map.x - minimap->offset.x) * MINI_MAP_SCALE;
	hit_minimap.y = (hit_map.y - minimap->offset.y) * MINI_MAP_SCALE;
	return (hit_minimap);
}

void	plot_line_low(t_vector2 start, t_vector2 end, t_minimap *minimap)
{
	t_vector2	delta;
	int			yi;
	int			d;

	delta = set_vector2(end.x - start.x, end.y - start.y);
	yi = 1;
	if (delta.y < 0)
	{
		yi = -1;
		delta.y = -delta.y;
	}
	d = (2 * delta.y) - delta.x;
	while (start.x <= end.x)
	{
		if (start.x < minimap->buffer.w && start.x >= 0
			&& start.y < minimap->buffer.h && start.y >= 0)
			*(minimap->buffer.addr + start.x + start.y * (int)WINDOW_WIDTH
					/ 8) = BLUE;
		if (d > 0)
		{
			start.y += yi;
			d = d + (2 * (delta.y - delta.x));
		}
		else
			d = d + 2 * delta.y;
		start.x++;
	}
}

void	plot_line_high(t_vector2 start, t_vector2 end, t_minimap *minimap)
{
	t_vector2 delta;
	int xi;
	int d;

	delta = set_vector2(end.x - start.x, end.y - start.y);
	xi = 1;
	if (delta.x < 0)
	{
		xi = -1;
		delta.x = -delta.x;
	}
	d = (2 * delta.x) - delta.y;
	while (start.y <= end.y)
	{
		if (start.x < minimap->buffer.w && start.x >= 0
			&& start.y < minimap->buffer.h && start.y >= 0)
			*(minimap->buffer.addr + start.x + start.y * (int)WINDOW_WIDTH
					/ 8) = BLUE;
		if (d > 0)
		{
			start.x = start.x + xi;
			d = d + (2 * (delta.x - delta.y));
		}
		else
			d = d + 2 * delta.x;
		start.y++;
	}
}