/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:30 by amalangu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/21 10:57:26 by amalangu         ###   ########.fr       */
=======
/*   Updated: 2026/01/23 22:11:43 by amalangu         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
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
	data->buffer.addr = (t_pxl *)mlx_get_data_addr(data->buffer.ptr,
			&data->buffer.bpp, &data->buffer.lenght, &data->buffer.end);
	if (!data->buffer.addr)
		exit_error("Getting buffer image address", data);
	data->buffer.w = WINDOW_WIDTH;
	data->buffer.h = WINDOW_HEIGHT;
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
}
