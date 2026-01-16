/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/16 11:25:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "struct.h"

void	raycast(t_cub3d *data);
void	raycast_thread(t_drawer *drawer);
int		get_texture_pixel_color(t_img texture, int text_x, int text_y);
int		get_texture_index(t_raycaster rc);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);
void	clear_image(t_cub3d *data);
void	draw_vertical_line(t_raycaster rc, t_cub3d *data);
void	pxl_put(t_cub3d *data, int x, int y, int color);
void	*draw_routine(void *args);

#endif