/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:39:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include <X11/keysym.h>

int	handle_keys(int key_stroked, t_cub3d *data)
{
	t_vector3	fwd;

	if (key_stroked == 65307)
		return (mlx_loop_end(data->mlx), 0);
	if (key_stroked == XK_Up)
		data->camera.y += 8.0f * data->timer.delta_time;
	if (key_stroked == XK_Down)
		data->camera.y -= 8.0f * data->timer.delta_time;
	if (key_stroked == XK_Right)
		data->camera.x -= 8.0f * data->timer.delta_time; // Travel Along X-Axis
	if (key_stroked == XK_Left)
		data->camera.x += 8.0f * data->timer.delta_time; // Travel Along X-Axis
	fwd = vector_mul(data->look_dir, 20.0f * data->timer.delta_time);
	if (key_stroked == XK_w)
		data->camera = vector_add(data->camera, fwd);
	if (key_stroked == XK_s)
		data->camera = vector_sub(data->camera, fwd);
	if (key_stroked == XK_d)
		data->yaw += 2.0f * data->timer.delta_time;
	if (key_stroked == XK_a)
		data->yaw -= 2.0f * data->timer.delta_time;
	return (0);
}

int	on_destroy(t_cub3d *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	clear_image(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			pxl_put(data, x++, y, 0, __FLT_MAX__);
		y++;
	}
}

void	clear_z_buffer(float **z_buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			z_buffer[y][x++] = __FLT_MAX__;
		y++;
	}
}

// void	fps_counter(double dt)
// {
// 	printf("%i fps\n", (int)(1 / dt));
// }

int	update(t_cub3d *data)
{
	get_current_time(data);
	clear_image(data);
	clear_z_buffer(data->z_buffer);
	process_mesh(data);
	mlx_put_image_to_window(data->mlx, data->window, data->image.ptr, 0, 0);
	return (0);
}

void	start_loop(t_cub3d *data)
{
	mlx_hook(data->window, 17, 0, on_destroy, data);
	mlx_hook(data->window, 2, (1L << 0), handle_keys, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}

void	free_cub3d(t_cub3d *data)
{
	t_triangle	*next;
	int			i;

	mlx_destroy_image(data->mlx, data->image.ptr);
	// mlx_destroy_image(data->mlx, data->object.texture.ptr);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	while (data->object.mesh)
	{
		next = data->object.mesh->next;
		free(data->object.mesh);
		data->object.mesh = next;
	}
	i = 0;
	while (i < WINDOW_HEIGHT)
		free(data->z_buffer[i++]);
	free(data->z_buffer);
}

int	main(void)
{
	t_cub3d data;
	ft_memset(&data, 0, sizeof(t_cub3d));
	set_mlx(&data);
	// data.object = load_obj_with_texture("cube.obj", "cube.png", data.mlx);
	data.object = load_obj("Tree1.obj");
	start_loop(&data);
	free_cub3d(&data);
	return (0);
}