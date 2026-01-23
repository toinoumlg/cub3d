/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/23 23:42:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "struct.h"

void	raycast(int **map, t_player *player, t_img *textures, t_pxl *buffer);
t_pxl	create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);
void	clear_image(t_pxl *buffer, int floor, int ceiling);
void	draw_vertical_line(int x, t_pxl *buffer, t_raycaster *rc);
void	find_perp_dist(int **map, t_double2 player_pos, t_raycaster *rc);

#endif