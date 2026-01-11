/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:25:46 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 12:46:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include "swap.h"


static int	handle_keys(int key_stroked, t_cub3d *data)
{
	if (key_stroked == XK_Escape)
		return (mlx_loop_end(data->mlx), 0);
	if (key_stroked == XK_Right)
		rotate(&data->player.dir, &data->plane, -ROTATION);
	if (key_stroked == XK_Left)
		rotate(&data->player.dir, &data->plane, ROTATION);
	if (key_stroked == XK_w)
		move_fwd(&data->player.dir, &data->player.pos, data->map,
			data->map_size);
	if (key_stroked == XK_s)
		move_bwd(&data->player.dir, &data->player.pos, data->map,
			data->map_size);
	if (key_stroked == XK_d)
		move_right(&data->player.dir, &data->player.pos, data->map,
			data->map_size);
	if (key_stroked == XK_a)
		move_left(&data->player.dir, &data->player.pos, data->map,
			data->map_size);
	return (0);
}

static int	on_destroy(t_cub3d *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	fps_counter(t_cub3d *data)
{
	char	*tmp;

	tmp = ft_itoa((int)(1 / data->timer.delta_time));
	mlx_string_put(data->mlx, data->window, 5, 10, __INT_MAX__, tmp);
	free(tmp);
}

static int	update_game(t_cub3d *data)
{
	get_current_time(data);
	clear_buffer(data);
	mlx_put_image_to_window(data->mlx, data->window, data->buffer.ptr, 0, 0);
	fps_counter(data);
	return (0);
}

void	game(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update_game, data);
	mlx_loop(data->mlx);
}
