/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:43:50 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/28 08:07:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "struct.h"
#include <stdlib.h>
#include <unistd.h>

void	free_config(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	free_map(int **map, int y)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < y)
		free(map[i++]);
	free(map);
}

static void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

static void	free_mlx(t_cub3d *data)
{
	if (data->buffer.ptr)
		mlx_destroy_image(data->mlx, data->buffer.ptr);
	if (data->textures[0].ptr)
		mlx_destroy_image(data->mlx, data->textures[0].ptr);
	if (data->textures[1].ptr)
		mlx_destroy_image(data->mlx, data->textures[1].ptr);
	if (data->textures[2].ptr)
		mlx_destroy_image(data->mlx, data->textures[2].ptr);
	if (data->textures[3].ptr)
		mlx_destroy_image(data->mlx, data->textures[3].ptr);
	if (data->textures[4].ptr)
		mlx_destroy_image(data->mlx, data->textures[4].ptr);
	if (data->textures[5].ptr)
		mlx_destroy_image(data->mlx, data->textures[5].ptr);
	if (data->minimap.buffer.ptr)
		mlx_destroy_image(data->mlx, data->minimap.buffer.ptr);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	free_cub3d(t_cub3d *data)
{
	free_mlx(data);
	free_map(data->minimap.array, data->minimap.size.y);
	free_config(data->config);
	ft_close(&data->fd);
	return (1);
}
