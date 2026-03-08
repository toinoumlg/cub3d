/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 13:27:20 by amalangu         ###   ########.fr       */
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

void		raycast(t_minimap *minimap, t_player *player, t_img *textures,
				t_pxl *buffer);
t_pxl		create_rgb(unsigned char r, unsigned char g, unsigned char b);
void		clear_image(t_pxl *buffer, int floor, int ceiling);
void		draw_vertical_line(int x, t_pxl *buffer, t_raycaster *rc);
void		find_perp_dist(char **map, t_double2 player_pos, t_raycaster *rc);
void		draw_minimap(t_minimap *minimap);
void		draw_lines_on_map(t_raycaster *rc, t_minimap *minimap,
				t_double2 *player_pos);
void		draw_player(t_minimap *minimap);
t_vector2	get_hit_pos_on_minimap(t_raycaster *rc, t_double2 *player_pos,
				t_minimap *minimap);
void		plot_line_high(t_vector2 start, t_vector2 end, t_minimap *minimap);
void		plot_line_low(t_vector2 start, t_vector2 end, t_minimap *minimap);

#endif