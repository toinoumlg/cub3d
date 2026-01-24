/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:19:43 by amalangu         ###   ########.fr       */
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

t_img	new_img(int widht, int height, t_cub3d *data)
{
	t_img	img;

	img.w = widht;
	img.h = height;
	img.ptr = mlx_new_image(data->mlx, widht, height);
	if (!img.ptr)
		exit_error("Initializing image", data);
	img.addr = (t_pxl *)mlx_get_data_addr(img.ptr, &img.bpp, &img.lenght,
			&img.end);
	if (!img.addr)
	{
		mlx_destroy_image(data->mlx, img.ptr);
		exit_error("Getting image address", data);
	}
	return (img);
}

void	init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Failed to initialize minilibx", data);
	data->buffer = new_img(WINDOW_WIDTH, WINDOW_HEIGHT, data);
	data->minimap.buffer = new_img(WINDOW_WIDTH / 8, WINDOW_WIDTH / 8, data);
	data->minimap.visible_square = set_double2((float)data->minimap.buffer.w
			/ MINI_MAP_SCALE / 2, (float)data->minimap.buffer.h / MINI_MAP_SCALE
			/ 2);
	data->minimap.player = set_vector2(data->minimap.buffer.w / 2 - 4,
			data->minimap.buffer.h / 2 - 4);
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
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (!data->window)
		exit_error("Failed to open new window", data);
}
