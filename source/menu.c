/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:25:51 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 18:47:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "swap.h"
#include <X11/keysym.h>
#include <stdlib.h>

static int	handle_keys(int key_stroked, t_cub3d *data)
{
	if (key_stroked == XK_Escape)
		return (mlx_loop_end(data->mlx), 0);
	return (0);
}

static int	on_destroy(t_cub3d *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	draw_menu(void)
{
}

void	fill_screen(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			pxl_put(data->menu.img, x++, y, data->floor);
		y++;
	}
}

int	update_menu(t_cub3d *data)
{
	get_current_time(data);
	fill_screen(data);
	draw_menu();
	mlx_put_image_to_window(data->mlx, data->window, data->menu.img.ptr, 0, 0);
	return (0);
}

void	menu(t_cub3d *data)
{
	mlx_mouse_get_pos(data->mlx, data->window, &data->menu.mouse.x,
		&data->menu.mouse.y);
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update_menu, data);
	mlx_loop(data->mlx);
}
