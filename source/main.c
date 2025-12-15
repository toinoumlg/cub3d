/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
/*   Updated: 2025/12/15 13:37:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "movement.h"
#include "swap.h"
#include <X11/keysym.h>
#include <stdio.h>

int	handle_keys(int key_stroked, t_cub3d *data)
{
	if (key_stroked == 65307)
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

int	on_destroy(t_cub3d *data)
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

int	update(t_cub3d *data)
{
	get_current_time(data);
	clear_image(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->buffer.ptr, 0, 0);
	fps_counter(data);
	return (0);
}

void	start_loop(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}

void	free_map(int **map, int y)
{
	int	i;

	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);
}

void	free_cub3d(t_cub3d *data)
{
	mlx_destroy_image(data->mlx, data->buffer.ptr);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free_map(data->map, data->map_size.y);
	free(data->mlx);
}

int	main(void)
{
	t_cub3d	data;

	ft_memset(&data, 0, sizeof(t_cub3d));
	init_data(&data);
	start_loop(&data);
	free_cub3d(&data);
	return (0);
}
