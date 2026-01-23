/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:56:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 00:16:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <X11/keysym.h>

int	key_released(int key, t_cub3d *data)
{
	if (key == XK_Right)
		data->player.inputs.right = 0;
	if (key == XK_Left)
		data->player.inputs.left = 0;
	if (key == XK_f)
		data->player.inputs.zoom = 0;
	if (key == XK_w)
		data->player.inputs.w = 0;
	if (key == XK_s)
		data->player.inputs.s = 0;
	if (key == XK_d)
		data->player.inputs.d = 0;
	if (key == XK_a)
		data->player.inputs.a = 0;
	return (0);
}

int	key_pressed(int key, t_cub3d *data)
{
	if (key == 65307)
		mlx_loop_end(data->mlx);
	if (key == XK_Right)
		data->player.inputs.right = 1;
	if (key == XK_Left)
		data->player.inputs.left = 1;
	if (key == XK_f)
		data->player.inputs.zoom = 1;
	if (key == XK_w)
		data->player.inputs.w = 1;
	if (key == XK_s)
		data->player.inputs.s = 1;
	if (key == XK_d)
		data->player.inputs.d = 1;
	if (key == XK_a)
		data->player.inputs.a = 1;
	return (0);
}
