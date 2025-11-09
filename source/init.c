/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:30 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/07 22:35:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"

t_img	new_image(void *mlx)
{
	t_img	new_img;

	new_img.ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	new_img.addr = mlx_get_data_addr(new_img.ptr, &new_img.bpp, &new_img.lenght,
			&new_img.end);
	return (new_img);
}

float	**init_z_buffer(void)
{
	int		y;
	float	**z_buffer;
	int		x;

	y = 0;
	z_buffer = malloc(sizeof(float *) * WINDOW_HEIGHT);
	while (y < WINDOW_HEIGHT)
	{
		z_buffer[y] = malloc(sizeof(float) * WINDOW_WIDTH);
		x = 0;
		while (x < WINDOW_WIDTH)
			z_buffer[y][x++] = __FLT_MAX__;
		y++;
	}
	return (z_buffer);
}

void	set_mlx(t_cub3d *data)
{
	set_timer(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	data->image = new_image(data->mlx);
	data->proj = matrix_make_projection();
	data->z_buffer = init_z_buffer();
}