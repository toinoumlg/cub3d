/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:18:05 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 11:50:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init_engine.c
 * @brief Initializes all components of the cub3D engine to default values.
 */

#include "cub3d.h"

/**
 * @brief Initialize the main engine structure to default values.
 *
 * Sets all fields of the t_engine structure to NULL, zero, or default states.
 *
 * @param engine Pointer to the main engine structure to initialize.
 */
void	init_engine(t_engine *engine)
{
	ft_memset(engine, 0, sizeof(t_engine));
	engine->win_width = WIN_WIDTH;
	engine->win_height = WIN_HEIGHT;
	engine->texinfo.size = TEX_SIZE;
	engine->mapinfo.fd = -1;
}
