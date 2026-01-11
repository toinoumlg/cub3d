/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:56 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/09 18:50:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>

typedef struct s_double2
{
	double			x;
	double			y;
}					t_double2;

typedef struct s_int2
{
	int				x;
	int				y;
}					t_int2;

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
	int				w;
	int				h;
	int				end;
}					t_img;

typedef struct s_raycaster
{
	t_double2		ray_dir;
	t_double2		camera;
	t_double2		d_dist;
	t_double2		s_dist;
	t_int2			map_pos;
	t_int2			step;
	int				x;
	int				side;
	int				hit;
	double			perp_dist;
}					t_raycaster;

double				ft_abs(double nb);
t_double2			set_double2(float x, float y);
t_int2				set_int2(int x, int y);

#endif