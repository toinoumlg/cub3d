/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:32:58 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:23:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_args(char *av, t_engine *engine)
{
	validate_file(av);
	load_file(av, engine);
	get_config(engine);
	set_player(engine);
	validate_map(engine, engine->map);
}

void	set_timer(t_engine *data)
{
	data->timer.time = 0.0f;
	gettimeofday(&data->timer.last_frame, NULL);
}

t_image	new_img(int widht, int height, t_engine *engine)
{
	t_image	new;

	new.ptr = mlx_new_image(engine->mlx, widht, height);
	if (!new.ptr)
		exit_free(engine, "buffer", ERROR_MLX_IMG, FAILURE);
	new.addr = (int *)mlx_get_data_addr(new.ptr, &new.pixel_bits,
			&new.size_line, &new.endian);
	if (!new.addr)
		exit_free(engine, "buffer addr", ERROR_MLX_IMG, FAILURE);
	new.w = widht;
	new.h = height;
	return (new);
}

void	init_minimap(t_minimap_ctx *minimap, t_engine *engine)
{
	minimap->buffer = new_img(WIN_WIDTH / 8, WIN_WIDTH / 8, engine);
	minimap->visible_square = minimap->buffer.h / MINIMAP_SCALE / 2;
	minimap->player.x = minimap->buffer.w / 2 - 4;
	minimap->player.y = minimap->buffer.w / 2 - 4;
}

void	init_window(t_engine *engine)
{
	engine->win = mlx_new_window(engine->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!engine->win)
		exit_free(engine, "mlx", ERROR_MLX_WIN, FAILURE);
	engine->buffer = new_img(WIN_WIDTH, WIN_HEIGHT, engine);
	if (BONUS)
		init_minimap(&engine->minimap, engine);
}

int	main(int argc, char **argv)
{
	t_engine	engine;

	ft_memset(&engine, 0, sizeof(t_engine));
	if (argc != 2)
		return (print_error_msg(NULL, ERROR_USAGE, FAILURE));
	init_mlx(&engine);
	parse_args(argv[1], &engine);
	init_window(&engine);
	register_input_hooks(&engine);
	mlx_loop_hook(engine.mlx, render, &engine);
	mlx_loop(engine.mlx);
	free_engine(&engine);
	return (0);
}
