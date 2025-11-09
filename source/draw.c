/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 20:49:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_swap(int *i, int *j)
{
	int	tmp;

	tmp = *i;
	*i = *j;
	*j = tmp;
}

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char[4]){b, g, r, t});
}

void	pxl_put(t_cub3d *data, int x, int y, int color, float z)
{
	char	*pxl;

	if (z > data->z_buffer[y][x])
		return ;
	data->z_buffer[y][x] = z;
	pxl = data->image.addr + (y * data->image.lenght + x * (data->image.bpp
				/ 8));
	*(unsigned int *)pxl = color;
}

void	draw_line(int x0, int y0, int x1, int y1, t_cub3d *data, int color,
		float z)
{
	char	steep;
	int		error;
	int		y;
	int		x;

	steep = 0;
	if (ft_abs(x0 - x1) < ft_abs(y0 - y1))
	{
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
		steep = 1;
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
	}
	error = 0;
	y = y0;
	x = x0;
	while (x <= x1)
	{
		if (steep)
			pxl_put(data, y, x, color, z);
		else
			pxl_put(data, x, y, color, z);
		error += 2 * ft_abs(y1 - y0);
		if (y1 > y0)
			y += 1 * (error > x1 - x0);
		else
			y += -1 * (error > x1 - x0);
		error -= 2 * (x1 - x0) * (error > x1 - x0);
		x++;
	}
}

void	draw_horizontal_line(int xmin, int xmax, int y, t_cub3d *data,
		int color, float z)
{
	int i = xmin;
	while (i <= xmax)
		pxl_put(data, i++, y, color, z);
}