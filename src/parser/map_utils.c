/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:27:13 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 20:36:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_utils.c
 * @brief Utility functions for map parsing and validation in the cub3D engine.
 */

#include "cub3d.h"

/**
 * @brief Check whether a character is considered whitespace.
 *
 * This function tests if the given character belongs to the set of
 * whitespace characters allowed in map files:
 * space, tab, carriage return, newline, vertical tab, or form feed.
 *
 * @param c Character to test.
 * @return SUCCESS if the character is a whitespace, FAILURE otherwise.
 */
int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (SUCCESS);
	return (FAILURE);
}
