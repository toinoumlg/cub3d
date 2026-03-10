/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:31:34 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 19:11:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "put.h"
#include <stdlib.h>

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

t_vector2	set_vector2(int x, int y)
{
	t_vector2	new_vector2;

	new_vector2.x = x;
	new_vector2.y = y;
	return (new_vector2);
}
