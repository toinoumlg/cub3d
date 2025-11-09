/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:56:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:01:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "png_to_img.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BITES_TO_READ 8

void	set_color(int x, int y, int color, t_img *texture)
{
	char	*pxl;

	pxl = texture->addr + (y * texture->lenght + x * (texture->bpp / 8));
	*(unsigned int *)pxl = color;
}

FILE	*init_png(char *file_name, t_png *png)
{
	FILE	*fp;

	fp = fopen(file_name, "rb");
	if (!fp)
		return (fp);
	png->p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png->info = png_create_info_struct(png->p);
	png_init_io(png->p, fp);
	png_read_info(png->p, png->info);
	png->width = png_get_image_width(png->p, png->info);
	png->height = png_get_image_height(png->p, png->info);
	png->color_type = png_get_color_type(png->p, png->info);
	png->bit_depth = png_get_bit_depth(png->p, png->info);
	return (fp);
}

void	set_png_info(t_png *png)
{
	if (png->bit_depth == 16)
		png_set_strip_16(png->p);
	if (png->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png->p);
	if (png->color_type == PNG_COLOR_TYPE_GRAY && png->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png->p);
	if (png_get_valid(png->p, png->info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png->p);
	if (png->color_type == PNG_COLOR_TYPE_RGB
		|| png->color_type == PNG_COLOR_TYPE_GRAY
		|| png->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png->p, 0xFF, PNG_FILLER_AFTER);
	if (png->color_type == PNG_COLOR_TYPE_GRAY
		|| png->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png->p);
	png_read_update_info(png->p, png->info);
}

void	copy_png_to_img(t_png *png, t_img *texture)
{
	png_byte	*row;
	png_bytep	px;
	int			y;
	int			x;

	y = 0;
	while (y < png->height)
	{
		row = png->rows[y];
		x = 0;
		while (x < png->width)
		{
			px = &(row[x * 4]);
			if (px[3] != 0)
				set_color(x, y, create_trgb(px[3], px[0], px[1], px[2]),
					texture);
			x++;
		}
		y++;
	}
}

void	free_png(t_png png)
{
	int	i;

	i = 0;
	while (i < png.height)
		free(png.rows[i++]);
	free(png.rows);
	png_destroy_info_struct(png.p, &png.info);
	png_destroy_read_struct(&png.p, NULL, NULL);
}

// from https://gist.github.com/jeroen/10eb17a9fb0e5799b772
void	png_to_img(char *file_name, t_img *texture, void *mlx)
{
	int		y;
	t_png	png;
	FILE	*fp;

	fp = init_png(file_name, &png);
	if (!fp)
		return ;
	set_png_info(&png);
	png.rows = malloc(sizeof(png_byte *) * png.height);
	y = 0;
	while (y < png.height)
		png.rows[y++] = malloc(png_get_rowbytes(png.p, png.info));
	png_read_image(png.p, png.rows);
	fclose(fp);
	texture->ptr = mlx_new_image(mlx, png.width, png.height);
	texture->w = png.width;
	texture->h = png.height;
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bpp,
			&texture->lenght, &texture->end);
	copy_png_to_img(&png, texture);
	free_png(png);
}
