/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:27:32 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 20:06:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"

void	plot_line_low_in(t_vector2 *start, t_img *buffer, int *d, int yi)
{
	if (start->x < buffer->w && start->x >= 0 && start->y < buffer->h
		&& start->y >= 0)
		*(buffer->addr + start->x + start->y * (int)WINDOW_WIDTH / 8) = YELLOW;
	if (*d > 0)
		start->y += yi;
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
		plot_line_low_in(&start, &minimap->buffer, &d, yi);
		if (d > 0)
			d = d + (2 * (delta.y - delta.x));
		else
			d = d + 2 * delta.y;
		start.x++;
	}
}

void	plot_line_high_in(t_vector2 *start, t_img *buffer, int *d, int xi)
{
	if (start->x < buffer->w && start->x >= 0 && start->y < buffer->h
		&& start->y >= 0)
		*(buffer->addr + start->x + start->y * (int)WINDOW_WIDTH / 8) = YELLOW;
	if (*d > 0)
		start->x = start->x + xi;
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
		plot_line_high_in(&start, &minimap->buffer, &d, xi);
		if (d > 0)
			d = d + (2 * (delta.x - delta.y));
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
