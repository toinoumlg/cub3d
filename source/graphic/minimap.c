/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:35:10 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 13:24:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

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

int	get_minimap_color(char **array, t_vector2 *coords, t_vector2 *size,
		t_double2 *offset)
{
	int		color;
	float	x;
	float	y;

	x = (float)coords->x / MINI_MAP_SCALE + offset->x;
	y = (float)coords->y / MINI_MAP_SCALE + offset->y;
	if (x >= size->x || y >= size->y || y < 0 || x < 0)
		return (BLACK);
	if (array[(int)y][(int)x] == '1')
		color = RED;
	else if (array[(int)y][(int)x] == '0')
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
