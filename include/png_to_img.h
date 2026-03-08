/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_png_to_img.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:23:52 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 21:05:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_TO_IMG
# define PNG_TO_IMG
# include <png.h>

typedef struct s_png
{
	png_struct	*p;
	png_info	*info;
	png_byte	**rows;
	png_byte	color_type;
	png_byte	bit_depth;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_png;

void			*mlx_png_to_img(char *path, void *mlx, int *width, int *heigth);

#endif