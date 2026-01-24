/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 01:29:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "struct.h"

# ifndef COLORS
#  define RED 0xFC0000
#  define BLACK 0
#  define WHITE 0xFFFFFF
#  define BLUE 0x0000FF
#  define GREEN 0x00FF00
# endif

void	raycast(int **map, t_player *player, t_img *textures, t_pxl *buffer,
			t_cub3d *data);
t_pxl	create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);
void	clear_image(t_pxl *buffer, int floor, int ceiling);
void	draw_vertical_line(int x, t_pxl *buffer, t_raycaster *rc);
void	find_perp_dist(int **map, t_double2 player_pos, t_raycaster *rc);
void	draw_map(t_cub3d *data);
void	draw_lines_on_map(t_raycaster rc, t_cub3d *data);

#endif