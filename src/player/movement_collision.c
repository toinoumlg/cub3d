/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:44:07 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 18:21:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file movement_collision.c
 * @brief Handles player movement with collision detection 
 * against walls and map boundaries.
 *
 * This file contains functions to validate player movement 
 * by checking for wall collisions and ensuring the player 
 * stays within the map boundaries. 
 * The logic differs based on whether the BONUS mode is enabled,
 * allowing for more precise
 * collision detection in the bonus version of the project.
 */

#include "cub3d.h"

