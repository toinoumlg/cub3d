/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:35:10 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 01:25:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

static void	set_map_offset(t_double2 *offset, t_cub3d *data)
{
	t_double2	visible_square;

	visible_square = set_double2((float)data->minimap.w / MINI_MAP_SCALE,
			(float)data->minimap.h / MINI_MAP_SCALE);
	if (visible_square.x < 1)
		visible_square.x = 1;
	if (visible_square.y < 1)
		visible_square.y = 1;
	offset->x = data->player.pos.x - (visible_square.x / 2);
	offset->y = data->player.pos.y - (visible_square.y / 2);
}

void	set_minimap_max_value(t_vector2 *hit_minimap, t_cub3d *data)
{
	if (hit_minimap->x < 0)
		hit_minimap->x = 0;
	if (hit_minimap->x >= data->minimap.w)
		hit_minimap->x = data->minimap.w - 1;
	if (hit_minimap->y < 0)
		hit_minimap->y = 0;
	if (hit_minimap->y >= data->minimap.h)
		hit_minimap->y = data->minimap.h - 1;
}

static t_vector2	get_hit_pos_on_minimap(t_raycaster rc, t_double2 player_pos,
		t_cub3d *data)
{
	t_double2	hit_map;
	t_double2	offset;
	t_vector2	hit_minimap;

	set_map_offset(&offset, data);
	hit_map.x = player_pos.x + rc.perp_dist * rc.ray_dir.x;
	hit_map.y = player_pos.y + rc.perp_dist * rc.ray_dir.y;
	hit_minimap.x = (hit_map.x - offset.x) * MINI_MAP_SCALE;
	hit_minimap.y = (hit_map.y - offset.y) * MINI_MAP_SCALE;
	return (hit_minimap);
}

void	plot_line_low(t_vector2 start, t_vector2 end, t_cub3d *data)
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
		if (start.x < data->minimap.w && start.x >= 0
			&& start.y < data->minimap.h && start.y >= 0)
			*(data->minimap.addr + start.x + start.y * (int)WINDOW_WIDTH
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

void	plot_line_high(t_vector2 start, t_vector2 end, t_cub3d *data)
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
		if (start.x < data->minimap.w && start.x >= 0
			&& start.y < data->minimap.h && start.y >= 0)
			*(data->minimap.addr + start.x + start.y * (int)WINDOW_WIDTH
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

void	draw_lines_on_map(t_raycaster rc, t_cub3d *data)
{
	t_vector2	end;
	t_vector2	start;

	start = set_vector2(data->minimap.w / 2, data->minimap.h / 2);
	end = get_hit_pos_on_minimap(rc, data->player.pos, data);
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			plot_line_low(end, start, data);
		else
			plot_line_low(start, end, data);
	}
	else
	{
		if (start.y > end.y)
			plot_line_high(end, start, data);
		else
			plot_line_high(start, end, data);
	}
}

int	get_minimap_color(t_cub3d *data, float x, float y, t_double2 offset)
{
	int	color;

	x = x / MINI_MAP_SCALE + offset.x;
	y = y / MINI_MAP_SCALE + offset.y;
	if (x >= data->map_size.x || y >= data->map_size.y || y < 0 || x < 0)
		return (BLACK);
	if (data->map[(int)y][(int)x] == 1)
		color = RED;
	else if (data->map[(int)y][(int)x] == 0)
		color = WHITE;
	else
		color = BLUE;
	return (color);
}

void	draw_player(t_cub3d *data)
{
	t_vector2	player;
	int			y;
	int			x;

	player = set_vector2(data->minimap.w / 2 - 4, data->minimap.h / 2 - 4);
	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
			*(data->minimap.addr + player.x + x++ + (player.y + y)
					* (int)WINDOW_WIDTH / 8) = GREEN;
		y++;
	}
}

void	draw_map(t_cub3d *data)
{
	t_double2	offset;
	int			color;
	int			x;
	int			y;

	y = 0;
	set_map_offset(&offset, data);
	while (y < data->minimap.h)
	{
		x = 0;
		while (x < data->minimap.w)
		{
			color = get_minimap_color(data, x, y, offset);
			*(data->minimap.addr + x++ + y * (int)WINDOW_WIDTH / 8) = color;
		}
		y++;
	}
	draw_player(data);
}
