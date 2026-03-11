/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:35:10 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 20:06:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

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
