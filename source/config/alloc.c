/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:50:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 11:37:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "mem.h"
#include "struct.h"
#include <stdlib.h>

void	alloc_map(t_cub3d *data)
{
	int	i;

	data->minimap.array = ft_calloc(sizeof(char *), (data->minimap.size.y + 1));
	if (!data->minimap.array)
		exit_error("Allocation failed during alloc_map", data);
	i = 0;
	while (i < data->minimap.size.y)
	{
		data->minimap.array[i] = ft_calloc(sizeof(char), (data->minimap.size.x
					+ 1));
		if (!data->minimap.array[i++])
			exit_error("Allocation failed during alloc_map", data);
	}
}

void	allocate_config(int size, t_cub3d *data)
{
	data->config = ft_calloc(sizeof(char *), (size + 1));
	if (!data->config)
		exit_error("Memory allocation failed.", NULL);
}
