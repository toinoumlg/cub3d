/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:43 by amalangu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/23 13:28:05 by amalangu         ###   ########.fr       */
=======
/*   Updated: 2026/01/24 00:17:30 by amalangu         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include "struct.h"
#include <stdio.h>

/// @brief clear the image with 2 color (floor/ceiling)
void	clear_image(t_pxl *buffer, int floor, int ceiling)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH / 2)
		buffer[i++] = floor;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
		buffer[i++] = ceiling;
}

void	shade(t_pxl *color, float shading)
{
	*color = (((int)((unsigned char)(*color >> 16) / shading) << 16)
			+ ((int)((unsigned char)(*color >> 8) / shading) << 8)
			+ ((int)((unsigned char)(*color >> 0) / shading) << 0));
}

void	draw_vertical_line(int x, t_pxl *buffer, t_raycaster *rc)
{
	t_pxl		color;
	t_double2	text_c;
	int			w;

	w = rc->text->w;
	text_c = rc->text_coord;
	while (rc->draw_limit.x < rc->draw_limit.y)
	{
		color = *(rc->text->addr + (int)text_c.x + (int)text_c.y * w);
		text_c.y += rc->step;
		// norminette ??
		*(buffer + x + rc->draw_limit.x++ * (int)WINDOW_WIDTH) = color;
	}
}
