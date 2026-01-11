/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:01:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 18:49:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "menu.h"
# include "mlx.h"
# include "utils.h"
# include <math.h>

# ifndef CONFIG
#  define CONFIG

#  define WINDOW_WIDTH 1280.0f
#  define WINDOW_HEIGHT 720.0f
#  define FPS 30.0f
#  define WINDOW_NAME "cub3d"
#  define BLACK 0
#  define SPEED 0.5
#  define ROTATION 0.1
# endif

typedef struct s_player
{
	t_double2		pos;
	t_double2		dir;
}					t_player;

typedef enum e_game_state
{
	main_menu,
	playing,
	dead,
	win
}					t_game_state;

typedef struct s_cub3d
{
	int				frames;
	void			*mlx;
	int				**map;
	t_double2		map_size;
	void			*window;
	int				floor;
	int				ceiling;
	t_menu			menu;
	t_img			textures[4];
	t_img			buffer;
	t_timer			timer;
	t_double2		plane;
	t_player		player;
	t_game_state	state;
}					t_cub3d;

void				init_data(t_cub3d *data);
void				menu(t_cub3d *data);
void				get_current_time(t_cub3d *data);
void				set_timer(t_cub3d *data);
int					create_trgb(unsigned char t, unsigned char r,
						unsigned char g, unsigned char b);
void				pxl_put(t_img img, int x, int y, int color);
void				raycast(t_cub3d *data);

void				draw_vert_line(int x, t_int2 draw_limit, int color,
						t_cub3d *data);
int					is_walkable(int **map, t_double2 map_size, int x, int y);
void				clear_buffer(t_cub3d *data);

#endif