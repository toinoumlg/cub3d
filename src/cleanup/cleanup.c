/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:46:20 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:23:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleanup.c
 * @brief Functions to safely free memory allocated
 * in the cub3D engine.
 */

#include "cub3d.h"

/**
 * @brief Frees a NULL-terminated 2D array.
 *
 * @param array Pointer to the 2D array to free.
 */
void	free_2d_array(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_textures(t_image *textures, void *mlx)
{
	if (!mlx)
		return ;
	if (textures[NORTH].ptr)
		mlx_destroy_image(mlx, textures[NORTH].ptr);
	if (textures[SOUTH].ptr)
		mlx_destroy_image(mlx, textures[SOUTH].ptr);
	if (textures[WEST].ptr)
		mlx_destroy_image(mlx, textures[WEST].ptr);
	if (textures[EAST].ptr)
		mlx_destroy_image(mlx, textures[EAST].ptr);
}

/**
 * @brief Frees all allocated memory in the engine.
 *
 * This includes:
 * - Texture arrays and pixel buffers
 * - Texture info
 * - Map context and map
 *
 * @param engine Pointer to the engine to free.
 * @return t_status_code FAILURE (always, used for
 * convenience in error handling)
 */
void	free_engine(t_engine *engine)
{
	if (engine->mlx && engine->buffer.ptr)
		mlx_destroy_image(engine->mlx, engine->buffer.ptr);
	free_textures(engine->textures, engine->mlx);
	free_2d_array((void **)engine->lines);
	free_2d_array((void **)engine->map);
	
	if (engine->mlx && engine->win)
		mlx_destroy_window(engine->mlx, engine->win);
	if (engine->mlx)
	{
		mlx_destroy_display(engine->mlx);
		free(engine->mlx);
	}
}

void	exit_free(t_engine *engine, char *detail, char *message, int code)
{
	print_error_msg(detail, message, code);
	free_engine(engine);
	exit(code);
}
