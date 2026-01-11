/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:31:34 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 18:49:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(int **map, t_double2 map_size, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)map_size.x || y >= (int)map_size.y)
		return (0);
	return (map[y][x] == 0);
}

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

t_double2	set_double2(float x, float y)
{
	t_double2	new_double2;

	new_double2.x = x;
	new_double2.y = y;
	return (new_double2);
}

t_int2	set_int2(int x, int y)
{
	t_int2	new_int2;

	new_int2.x = x;
	new_int2.y = y;
	return (new_int2);
}
