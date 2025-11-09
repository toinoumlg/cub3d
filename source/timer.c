/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:21:08 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 19:00:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"

void	set_timer(t_cub3d *data)
{
	data->timer.time = 0.0f;
	gettimeofday(&data->timer.last_frame, NULL);
}

void	get_current_time(t_cub3d *data)
{
	gettimeofday(&data->timer.current_time, NULL);

	data->timer.delta_time = (data->timer.current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (data->timer.current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
	data->timer.time += data->timer.delta_time;
	data->timer.last_frame = data->timer.current_time;
}