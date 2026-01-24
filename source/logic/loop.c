/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:19 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:25:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "logic.h"
#include "struct.h"
#include "swap.h"
#include <stdlib.h>

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
	clear_image(data->buffer.addr, data->floor, data->ceiling);
	apply_motion(data);
	draw_minimap(&data->minimap);
	raycast(&data->minimap, &data->player, data->textures, data->buffer.addr);
	draw_player(&data->minimap);
	mlx_put_image_to_window(data->mlx, data->window, data->buffer.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->window, data->minimap.buffer.ptr,
		20, 20);
	fps_counter(data);
	mlx_do_sync(data->mlx);
	return (0);
}

void	loop(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), key_pressed, data);
	mlx_hook(data->window, 3, (1L << 1), key_released, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}
