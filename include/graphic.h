/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/21 12:11:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

#ifndef COLORS
#define RED 0xFC0000
#define BLACK 0
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#endif

# include "struct.h"

void	raycast(t_cub3d *data);
void	draw_line_on_map(t_raycaster rc, t_cub3d *data);
void	draw_map(t_cub3d *data);
int		get_texture_pixel_color(t_img texture, int text_x, int text_y);
int		get_texture_index(t_raycaster rc);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);
void	clear_image(t_cub3d *data);
void	draw_vertical_line(t_raycaster rc, t_cub3d *data);
void	pxl_put(t_img img, int x, int y, int color);

#endif