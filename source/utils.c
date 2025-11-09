/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:31:34 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 16:32:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector3	set_vector3(float x, float y, float z)
{
	t_vector3	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	return (new_v);
}

float	ft_atof(const char *str)
{
	int i;
	int sign;
	float result;
	float place;

	i = 0;
	sign = 1;
	result = 0.0f;
	place = 0.1f;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] != ' ' && str[i] >= '0' && str[i] <= '9')
		result = result * 10.0f + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] && str[i] != ' ' && str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * place;
			place *= 0.1f;
		}
	}
	return (result * sign);
}