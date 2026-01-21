/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/18 09:14:33 by amalangu         ###   ########.fr       */
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
		rotate(&data->player.dir, &data->plane, -ROTATION);
	if (key_stroked == XK_Left)
		rotate(&data->player.dir, &data->plane, ROTATION);
	if (key_stroked == XK_w)
		move(&data->player.dir, data, SPEED);
	if (key_stroked == XK_s)
		move(&data->player.dir, data, -SPEED);
	if (key_stroked == XK_d)
		move(&data->plane, data, SPEED);
	if (key_stroked == XK_a)
		move(&data->plane, data, -SPEED);
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

	tmp = ft_itoa((int)(1 / data->timer.delta_time));
	mlx_string_put(data->mlx, data->window, 5, 10, __INT_MAX__, tmp);
	free(tmp);
}

static int	update(t_cub3d *data)
{
	get_current_time(data);
	pthread_mutex_lock(&data->th_data.mutex);
	while (data->th_data.draw_finished < THREAD_COUNT)
		pthread_cond_wait(&data->th_data.cond, &data->th_data.mutex);
	data->th_data.frame = 0;
	pthread_cond_broadcast(&data->th_data.cond);
	pthread_mutex_unlock(&data->th_data.mutex);
	mlx_put_image_to_window(data->mlx, data->window, data->buffer.ptr, 0, 0);
	mlx_do_sync(data->mlx);
	fps_counter(data);
	pthread_mutex_lock(&data->th_data.mutex);
	data->th_data.draw_finished = 0;
	data->th_data.frame = 1;
	pthread_cond_broadcast(&data->th_data.cond);
	pthread_mutex_unlock(&data->th_data.mutex);
	return (0);
}

void	loop(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}
