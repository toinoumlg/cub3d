/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:01:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/09 13:44:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "mlx.h"
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

# ifndef CONFIG
#  define WINDOW_WIDTH 1920.0f
#  define WINDOW_HEIGHT 1080.0f
#  define WINDOW_NAME "cub3d"
#  define FOV 70.0f
#  define MINI_MAP_SCALE 32
# endif

typedef unsigned int	t_pxl;

typedef struct s_input
{
	bool				w;
	bool				a;
	bool				s;
	bool				d;
	bool				left;
	bool				right;
	bool				zoom;
}						t_input;

typedef struct s_double2
{
	double				x;
	double				y;
}						t_double2;

typedef struct s_vector2
{
	int					x;
	int					y;
}						t_vector2;

typedef struct s_timer
{
	struct timeval		last_frame;
	struct timeval		current_time;
	double				time;
	double				delta_time;
}						t_timer;

typedef struct s_img
{
	void				*ptr;
	t_pxl				*addr;
	int					bpp;
	int					lenght;
	int					end;
	int					w;
	int					h;
}						t_img;

typedef struct s_player
{
	t_double2			pos;
	t_double2			dir;
	t_double2			plane;
	bool				zoom;
	t_input				inputs;
}						t_player;

typedef struct s_raycaster
{
	t_img				*text;
	t_double2			d_dist;
	t_double2			s_dist;
	t_double2			ray_dir;
	t_double2			text_coord;
	t_vector2			draw_limit;
	int					line_height;
	float				camera_x;
	int					side;
	double				perp_dist;
	double				step;
}						t_raycaster;

typedef struct s_minimap
{
	t_img				buffer;
	char				**array;
	t_vector2			size;
	t_double2			offset;
	t_double2			visible_square;
	t_vector2			player;
}						t_minimap;

typedef struct s_cub3d
{
	int					fd;
	void				*mlx;
	char				**config;
	void				*window;
	int					floor;
	int					ceiling;
	t_img				textures[4];
	t_img				buffer;
	t_timer				timer;
	t_player			player;
	t_minimap			minimap;
}						t_cub3d;

#endif