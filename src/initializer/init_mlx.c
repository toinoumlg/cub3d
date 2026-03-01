/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:51 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 17:58:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init_mlx.c
 * @brief Initializes the MiniLibX context, creates the main window,
 * and loads texture images for the cub3D engine.
 */
#include "cub3d.h"

/**
 * @brief Initialize MiniLibX and create the main window.
 *
 * Starts the MLX context, creates the main rendering window,
 * and applies bonus-related initializations when enabled.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_mlx(t_engine *engine)
{
	engine->mlx = mlx_init();
	if (!engine->mlx)
		exit_free(engine, "mlx", ERROR_MLX_START, FAILURE);
	if (BONUS)
		mlx_center_mouse(engine);
}
