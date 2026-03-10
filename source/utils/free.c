/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:43:50 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 19:14:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "struct.h"
#include <stdlib.h>
#include <unistd.h>

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
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
	free_array(data->minimap.array);
	free_array(data->config);
	ft_close(&data->fd);
	return (1);
}

void	exit_error(char *error, t_cub3d *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	if (data)
		free_cub3d(data);
	exit(1);
}
