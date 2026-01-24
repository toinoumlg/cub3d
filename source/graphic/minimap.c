/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:35:10 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:30:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

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

static t_vector2	get_hit_pos_on_minimap(t_raycaster *rc,
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
	t_vector2	delta;
	int			xi;
	int			d;

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

void	draw_lines_on_map(t_raycaster *rc, t_minimap *minimap,
		t_double2 *player_pos)
{
	t_vector2	end;
	t_vector2	start;

	start = set_vector2(minimap->buffer.w / 2, minimap->buffer.h / 2);
	end = get_hit_pos_on_minimap(rc, player_pos, minimap);
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			plot_line_low(end, start, minimap);
		else
			plot_line_low(start, end, minimap);
	}
	else
	{
		if (start.y > end.y)
			plot_line_high(end, start, minimap);
		else
			plot_line_high(start, end, minimap);
	}
}

int	get_minimap_color(int **array, t_vector2 *coords, t_vector2 *size,
		t_double2 *offset)
{
	int		color;
	float	x;
	float	y;

	x = (float)coords->x / MINI_MAP_SCALE + offset->x;
	y = (float)coords->y / MINI_MAP_SCALE + offset->y;
	if (x >= size->x || y >= size->y || y < 0 || x < 0)
		return (BLACK);
	if (array[(int)y][(int)x] == 1)
		color = RED;
	else if (array[(int)y][(int)x] == 0)
		color = WHITE;
	else
		color = BLUE;
	return (color);
}

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;

	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
			*(minimap->buffer.addr + minimap->player.x + x++
					+ (minimap->player.y + y) * (int)WINDOW_WIDTH / 8) = GREEN;
		y++;
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int			color;
	t_vector2	coords;

	coords.y = 0;
	while (coords.y < minimap->buffer.h)
	{
		coords.x = 0;
		while (coords.x < minimap->buffer.w)
		{
			color = get_minimap_color(minimap->array, &coords, &minimap->size,
					&minimap->offset);
			*(minimap->buffer.addr + coords.x++ + coords.y * (int)WINDOW_WIDTH
					/ 8) = color;
		}
		coords.y++;
	}
}
