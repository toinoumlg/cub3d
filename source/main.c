/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 12:46:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "menu.h"
#include <stdio.h>

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
	menu(&data);
	free_cub3d(&data);
	return (0);
}
