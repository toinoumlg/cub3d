/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:00:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/08 12:02:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "str.h"

t_vector3	vector_add(t_vector3 v1, t_vector3 v2)
{
	t_vector3	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

t_vector3	vector_sub(t_vector3 v1, t_vector3 v2)
{
	t_vector3	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return (new_v);
}

t_vector3	vector_mul(t_vector3 v, float mult)
{
	t_vector3	new_v;

	new_v.x = v.x * mult;
	new_v.y = v.y * mult;
	new_v.z = v.z * mult;
	return (new_v);
}

t_vector3	vector_div(t_vector3 v, float div)
{
	t_vector3	new_v;

	new_v.x = v.x / div;
	new_v.y = v.y / div;
	new_v.z = v.z / div;
	return (new_v);
}

float	vector_dot_product(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vector_lenght(t_vector3 v)
{
	return (sqrtf(vector_dot_product(v, v)));
}

t_vector3	vector_normalize(t_vector3 v)
{
	t_vector3	new_v;
	float		l;

	l = vector_lenght(v);
	new_v.x = v.x / l;
	new_v.y = v.y / l;
	new_v.z = v.z / l;
	return (new_v);
}

t_vector3	vector_cross_product(t_vector3 v1, t_vector3 v2)
{
	t_vector3 new_v;
	new_v.x = v1.y * v2.z - v1.z * v2.y;
	new_v.y = v1.z * v2.x - v1.x * v2.z;
	new_v.z = v1.x * v2.y - v1.y * v2.x;
	return (new_v);
}