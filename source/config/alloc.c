/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:50:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 02:30:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "mem.h"
#include "struct.h"
#include <stdlib.h>

void	alloc_map(t_cub3d *data)
{
	int	i;

	data->minimap.array = malloc(sizeof(int *) * data->minimap.size.y);
	if (!data->minimap.array)
		exit_error("Allocation failed during alloc_map", data);
	i = 0;
	while (i < data->minimap.size.y)
	{
		data->minimap.array[i] = malloc(sizeof(int) * data->minimap.size.x);
		if (!data->minimap.array[i])
		{
			data->minimap.size.y = i;
			exit_error("Allocation failed during alloc_map", data);
		}
		ft_memset(data->minimap.array[i++], -1, sizeof(int)
			* data->minimap.size.x);
	}
}

void	allocate_config(int size, t_cub3d *data)
{
	data->config = malloc(sizeof(char *) * (size + 1));
	if (!data->config)
		exit_error("Memory allocation failed.", NULL);
	ft_memset(data->config, 0, sizeof(char *) * (size + 1));
}
