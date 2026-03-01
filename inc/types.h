/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:07:18 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:01:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file types.h
 * @brief Definitions of core enums and structures for cub3D engine.
 */

#ifndef TYPES_H
# define TYPES_H
# include <stdbool.h>
# include <sys/time.h>
typedef unsigned long	t_ulong;

/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

/**
 * @enum e_status_code
 * @brief Represents generic return or control codes used throughout the engine.
 */
typedef enum e_status_code
{
	SUCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
}						t_status_code;

/**
 * @enum e_wall_direction
 * @brief Enum to index wall textures based on their orientation.
 */
typedef enum e_wall_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}						t_direction;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

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

/**
 * @struct t_image
 * @brief Represents a MiniLibX image buffer.
 */
typedef struct s_image
{
	void				*ptr;
	int					*addr;
	int					pixel_bits;
	int					size_line;
	int					endian;
	int					w;
	int					h;
}						t_image;

/**
 * @struct t_minimap_ctx
 * @brief Contains all data for rendering the minimap.
 */
typedef struct s_minimap_ctx
{
	t_image				buffer;
	t_vector2			offset;
	t_vector2			player;
	int					visible_square;
}						t_minimap_ctx;

/**
 * @struct t_raycast
 * @brief Contains all variables used during raycasting.
 */
typedef struct s_raycast
{
	t_double2			sidedist;
	t_double2			deltadist;
	t_double2			dir;
	t_double2			texture_coord;
	t_direction			wall_dir;
	int					side;
	double				step;
	double				wall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_raycast;

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

/**
 * @struct t_player
 * @brief Stores the player position, direction and movement state.
 */
typedef struct s_player
{
	t_double2			dir;
	t_double2			pos;
	t_double2			plane;
	t_double2			move;
	t_input				inputs;
}						t_player;

typedef struct s_timer
{
	struct timeval		last_frame;
	struct timeval		current_time;
	double				time;
	double				delta_time;
}						t_timer;

/**
 * @struct t_engine
 * @brief The main context of the cub3D engine containing all runtime data.
 */
typedef struct s_engine
{
	void				*mlx;
	void				*win;
	char				**map;
	t_player			player;
	t_raycast			ray;
	t_image				textures[4];
	t_image				buffer;
	t_vector2			map_size;
	char				**lines;
	int					floor;
	int					ceiling;
	t_minimap_ctx		minimap;
	t_timer				timer;
}						t_engine;

#endif
