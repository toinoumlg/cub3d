/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:56:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 10:48:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <X11/keysym.h>

int	key_released(int key, t_cub3d *data)
{
	if (key == XK_Right)
		data->player.inputs.right = false;
	if (key == XK_Left)
		data->player.inputs.left = false;
	if (key == XK_f)
		data->player.inputs.zoom = false;
	if (key == XK_w)
		data->player.inputs.w = false;
	if (key == XK_s)
		data->player.inputs.s = false;
	if (key == XK_d)
		data->player.inputs.d = false;
	if (key == XK_a)
		data->player.inputs.a = false;
	return (0);
}

int	key_pressed(int key, t_cub3d *data)
{
	if (key == 65307)
		mlx_loop_end(data->mlx);
	if (key == XK_Right)
		data->player.inputs.right = true;
	if (key == XK_Left)
		data->player.inputs.left = true;
	if (key == XK_f)
		data->player.inputs.zoom = true;
	if (key == XK_w)
		data->player.inputs.w = true;
	if (key == XK_s)
		data->player.inputs.s = true;
	if (key == XK_d)
		data->player.inputs.d = true;
	if (key == XK_a)
		data->player.inputs.a = true;
	return (0);
}
