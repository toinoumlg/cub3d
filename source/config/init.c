/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/16 12:08:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "graphic.h"
#include "mem.h"
#include "str.h"

int	*copy_line(char *str, int len)
{
	int	i;
	int	*row;

	i = 0;
	row = malloc(sizeof(int) * len);
	while (i < len)
	{
		row[i] = str[i] - '0';
		i++;
	}
	return (row);
}

void	init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Failed to initialize minilibx", data);
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (!data->window)
		exit_error("Failed to open new window", data);
	data->buffer.ptr = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->buffer.ptr)
		exit_error("Initializing buffer image", data);
	data->buffer.addr = mlx_get_data_addr(data->buffer.ptr, &data->buffer.bpp,
			&data->buffer.lenght, &data->buffer.end);
	if (!data->buffer.addr)
		exit_error("Getting buffer image address", data);
}

void	start_drawer_threads(t_drawer *drawer, t_cub3d *data)
{
	int	i;
	int	width_size;

	i = 0;
	width_size = WINDOW_WIDTH / THREAD_COUNT;
	while (i < THREAD_COUNT)
	{
		drawer[i].thread_limit = set_vector2(i * width_size, (i + 1)
				* width_size);
		drawer[i].data = data;
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		if (pthread_create(&drawer[i].thread, NULL, draw_routine, &drawer[i]))
			return (exit_error("Failed to initialize a thread", drawer->data));
		i++;
	}
}

void	init_cub3d(t_cub3d *data, int ac, char *file)
{
	int	size;

	ft_memset(data, 0, sizeof(t_cub3d));
	if (ac != 2)
		exit_error("No config file provided", data);
	size = try_open(file);
	init_mlx(data);
	copy_config(size, file, data);
	parse_config(data);
	set_timer(data);
	data->th_data.draw_finished = 1;
	pthread_mutex_init(&data->th_data.mutex, NULL);
	pthread_cond_init(&data->th_data.cond, NULL);
	start_drawer_threads(data->drawer_threads, data);
}
