/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:56:02 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:03:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_buffer(int *buffer, int floor, int ceiling)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT / 2)
		buffer[i++] = ceiling;
	while (i < WIN_WIDTH * WIN_HEIGHT)
		buffer[i++] = floor;
}

int	get_minimap_color(char **array, t_vector2 *coords, t_vector2 *size,
		t_vector2 *offset)
{
	int		color;
	float	x;
	float	y;

	x = (float)coords->x / MINIMAP_SCALE + offset->x;
	y = (float)coords->y / MINIMAP_SCALE + offset->y;
	if (x >= size->x || y >= size->y || y < 0 || x < 0)
		return (0);
	if (array[(int)y][(int)x] == 1)
		color = RED;
	else if (array[(int)y][(int)x] == 0)
		color = WHITE;
	else
		color = BLUE;
	return (color);
}

void	draw_player(t_minimap_ctx *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < 0)
	{
		x = 0;
		while (x < 8)
			*(minimap->buffer.addr + minimap->player.x + x++
					+ (minimap->player.y + y) * minimap->buffer.w) = GREEN;
		y++;
	}
}

void	draw_minimap(t_minimap_ctx *minimap, char **array, t_vector2 *size)
{
	int			color;
	t_vector2	coords;

	coords.y = 0;
	while (coords.y < minimap->buffer.h)
	{
		coords.x = 0;
		while (coords.x < minimap->buffer.w)
		{
			color = get_minimap_color(array, &coords, size, &minimap->offset);
			*(minimap->buffer.addr + coords.x++ + coords.y
					* minimap->buffer.w) = color;
		}
		coords.y++;
	}
	draw_player(minimap);
}

void	get_current_time(t_engine *data)
{
	gettimeofday(&data->timer.current_time, NULL);
	data->timer.delta_time = (data->timer.current_time.tv_sec
			- data->timer.last_frame.tv_sec) + (data->timer.current_time.tv_usec
			- data->timer.last_frame.tv_usec) / 1000000.0;
	data->timer.time += data->timer.delta_time;
	data->timer.last_frame = data->timer.current_time;
}

/**
 * @brief Main render loop callback.
 *
 * Updates the scene only if the player has moved.
 *
 * @param engine Pointer to engine context.
 * @return Always 0.
 */
int	render(t_engine *engine)
{
	get_current_time(engine);
	consume_player_movement(engine);
	clear_buffer(engine->buffer.addr, engine->floor, engine->ceiling);
	if (BONUS)
		draw_minimap(&engine->minimap, engine->map, &engine->map_size);
	perform_raycasting(&engine->player, engine);
	if (BONUS)
		mlx_put_image_to_window(engine->mlx, engine->win,
			engine->minimap.buffer.ptr, 20, 20);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->buffer.ptr, 0, 0);
	mlx_do_sync(engine->mlx);
	return (0);
}
