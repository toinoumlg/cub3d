/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:43 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 18:36:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char[4]){b, g, r, t});
}

int	addr_offset(t_img img, int x, int y)
{
	return (y * img.lenght + x * (img.bpp / 8));
}

void	pxl_put(t_img img, int x, int y, int color)
{
	char	*pxl;

	pxl = img.addr + addr_offset(img, x, y);
	*(unsigned int *)pxl = color;
}

void	clear_buffer(t_cub3d *data)
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

void	draw_vert_line(int x, t_int2 draw_limit, int color, t_cub3d *data)
{
	while (draw_limit.x < draw_limit.y)
	{
		pxl_put(data->buffer, x, draw_limit.x, color);
		draw_limit.x++;
	}
}
