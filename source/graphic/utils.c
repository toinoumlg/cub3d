/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:29:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:43:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

static int	addr_offset(t_img buffer, int x, int y)
{
	return (y * buffer.lenght + x * (buffer.bpp / 8));
}

void	pxl_put(t_cub3d *data, int x, int y, int color)
{
	char	*pxl;

	pxl = data->buffer.addr + addr_offset(data->buffer, x, y);
	*(unsigned int *)pxl = color;
}

int	get_texture_pixel_color(t_img texture, int text_x, int text_y)
{
	char	*pxl;

	pxl = texture.addr + addr_offset(texture, text_x, text_y);
	return (*(unsigned int *)pxl);
}

int	get_texture_index(t_raycaster rc)
{
	if (!rc.side)
	{
		if ((rc.ray_dir.x > 0))
			return (1);
		else
			return (3);
	}
	else
	{
		if ((rc.ray_dir.y > 0))
			return (2);
		else
			return (0);
	}
}
