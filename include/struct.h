/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:01:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/22 12:16:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "mlx.h"
# include <math.h>
# include <sys/time.h>

# ifndef CONFIG
#  define WINDOW_WIDTH 1920.0f
#  define WINDOW_HEIGHT 1080.0f
#  define WINDOW_NAME "cub3d"
#  define ROTATION 0.1
# endif

typedef struct s_double2
{
	double			x;
	double			y;
}					t_double2;

typedef struct s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct s_timer
{
	struct timeval	last_frame;
	struct timeval	current_time;
	double			time;
	double			delta_time;
}					t_timer;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				lenght;
	int				end;
	int				w;
	int				h;
}					t_img;

typedef struct s_player
{
	t_double2		pos;
	t_double2		dir;
}					t_player;

typedef struct s_raycaster
{
	t_double2		ray_dir;
	t_double2		camera;
	t_double2		d_dist;
	t_double2		s_dist;
	t_double2		texture;
	t_vector2		draw_limit;
	t_vector2		map_pos;
	t_vector2		step;
	int				x;
	int				side;
	int				line_height;
	double			perp_dist;
	double			wall_x;
	double			texture_step;
}					t_raycaster;

typedef struct s_cub3d
{
	int				fd;
	void			*mlx;
	int				**map;
	char			**config;
	t_vector2		map_size;
	void			*window;
	int				floor;
	int				ceiling;
	t_img			textures[4];
	t_img			buffer;
	t_timer			timer;
	t_double2		plane;
	t_player		player;
}					t_cub3d;

#endif