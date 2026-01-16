/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:41:35 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/16 13:46:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include "struct.h"

static void	clear_image_split(t_drawer *drawer)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = drawer->thread_limit.x;
		while (x < drawer->thread_limit.y)
			pxl_put(drawer->data, x++, y, drawer->data->floor);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = drawer->thread_limit.x;
		while (x < drawer->thread_limit.y)
			pxl_put(drawer->data, x++, y, drawer->data->ceiling);
		y++;
	}
}

void	*draw_routine(void *args)
{
	t_drawer *drawer = (t_drawer *)args;

	while (1)
	{
		clear_image_split(drawer);
		raycast_thread(drawer);
		pthread_mutex_lock(&drawer->data->th_data.mutex);
		drawer->data->th_data.draw_finished++;
		pthread_mutex_unlock(&drawer->data->th_data.mutex);
		pthread_cond_broadcast(&drawer->data->th_data.cond);
		pthread_mutex_lock(&drawer->data->th_data.mutex);
		while (drawer->data->th_data.draw_finished != 0)
			pthread_cond_wait(&drawer->data->th_data.cond,
				&drawer->data->th_data.mutex);
		pthread_mutex_unlock(&drawer->data->th_data.mutex);
	}
}
