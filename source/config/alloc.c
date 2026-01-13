/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:50:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:55:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "mem.h"
#include "struct.h"
#include <stdlib.h>

void	alloc_map(t_cub3d *data)
{
	int	i;

	data->map = malloc(sizeof(int *) * data->map_size.y);
	if (!data->map)
		exit_error("Allocation failed during alloc_map", data);
	i = 0;
	while (i < data->map_size.y)
	{
		data->map[i] = malloc(sizeof(int) * data->map_size.x);
		if (!data->map[i])
		{
			data->map_size.y = i;
			exit_error("Allocation failed during alloc_map", data);
		}
		ft_memset(data->map[i++], -1, sizeof(int) * data->map_size.x);
	}
}

void	allocate_config(int size, t_cub3d *data)
{
	data->config = malloc(sizeof(char *) * (size + 1));
	if (!data->config)
		exit_error("Memory allocation failed.", NULL);
	ft_memset(data->config, 0, sizeof(char *) * (size + 1));
}
