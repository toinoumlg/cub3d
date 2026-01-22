/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/21 10:38:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "logic.h"
#include "struct.h"
#include "swap.h"
#include <X11/keysym.h>
#include <stdlib.h>

static int	handle_keys(int key_stroked, t_cub3d *data)
{
	if (key_stroked == 65307)
		return (mlx_loop_end(data->mlx), 0);
	if (key_stroked == XK_Right)
		rotate(&data->player.dir, &data->plane, -1, data->timer.delta_time);
	if (key_stroked == XK_Left)
		rotate(&data->player.dir, &data->plane, 1, data->timer.delta_time);
	if (key_stroked == XK_w)
		move(&data->player.dir, data, 2);
	if (key_stroked == XK_s)
		move(&data->player.dir, data, -2);
	if (key_stroked == XK_d)
		move(&data->plane, data, 2);
	if (key_stroked == XK_a)
		move(&data->plane, data, -2);
	return (0);
}

static int	on_destroy(t_cub3d *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

static void	fps_counter(t_cub3d *data)
{
	char	*tmp;

	// char	*join;
	tmp = ft_itoa((int)(1 / data->timer.delta_time));
	mlx_string_put(data->mlx, data->window, 5, 10, __INT_MAX__, tmp);
	free(tmp);
	// tmp = ft_itoa(data->player.pos.)
	// mlx_string_put(data->mlx, data->window, 5, 20, __INT_MAX__, tmp);
}

static int	update(t_cub3d *data)
{
	get_current_time(data);
	clear_image(data);
	draw_map(data);
	raycast(data);
	fps_counter(data);
	mlx_put_image_to_window(data->mlx, data->window, data->buffer.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->window, data->minimap.ptr, 20, 20);
	fps_counter(data);
	return (0);
}

void	loop(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}
