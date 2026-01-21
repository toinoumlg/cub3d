/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:01:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/18 09:01:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <sys/time.h>

# ifndef CONFIG
#  define WINDOW_WIDTH 1280.0f
#  define WINDOW_HEIGHT 720.0f
#  define FPS 30.0f
#  define WINDOW_NAME "cub3d"
#  define BLACK 0
#  define SPEED 0.5
#  define ROTATION 0.1
#  define THREAD_COUNT 8
# endif

typedef struct s_cub3d	t_cub3d;

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
	char				*addr;
	int					bpp;
	int					lenght;
	int					w;
	int					h;
	int					end;
}						t_img;

typedef struct s_player
{
	t_double2			pos;
	t_double2			dir;
}						t_player;

typedef struct s_raycaster
{
	t_double2			ray_dir;
	t_double2			camera;
	t_double2			d_dist;
	t_double2			s_dist;
	t_double2			texture;
	t_vector2			draw_limit;
	t_vector2			map_pos;
	t_vector2			step;
	int					x;
	int					side;
	int					line_height;
	double				perp_dist;
	double				wall_x;
	double				texture_step;
}						t_raycaster;

typedef struct s_drawer
{
	pthread_t			thread;
	t_vector2			thread_limit;
	t_cub3d				*data;
}						t_drawer;

typedef struct s_thread_data
{
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	int					draw_finished;
	int					frame;
}						t_thread_data;

typedef struct s_cub3d
{
	int					fd;
	void				*mlx;
	int					**map;
	char				**config;
	t_vector2			map_size;
	void				*window;
	int					floor;
	int					ceiling;
	t_img				textures[4];
	t_img				buffer;
	t_timer				timer;
	t_double2			plane;
	t_player			player;
	t_thread_data		th_data;
	t_drawer			drawer_threads[THREAD_COUNT];
}						t_cub3d;

#endif