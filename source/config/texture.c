/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:04:29 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/28 08:06:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "config.h"
#include "cub_utils.h"
#include "graphic.h"
#include "mem.h"
#include "str.h"
#include "swap.h"

int	check_rgb(char *rgb, t_cub3d *data)
{
	int	i;
	int	color;

	i = 0;
	if (!rgb)
		exit_error("Missing value(s) for rbg color", data);
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]) && rgb[i] != ' ' && rgb[i] != '\t')
		{
			free(rgb);
			exit_error("Rbg value contain a character", data);
		}
		i++;
	}
	color = ft_atoi(rgb);
	free(rgb);
	if (color < 0 || color > 255)
		exit_error("Rgb value is outside of it's range", data);
	return (color);
}

int	set_color_from_config(char *to_find, char **config, t_cub3d *data)
{
	char	*line;
	char	**rgb;
	t_pxl	color;

	line = find_in_config(to_find, config);
	if (!line)
		exit_error("Missing rgb values in config file", data);
	line += ft_strlen(to_find);
	rgb = ft_split(line, ',');
	if (!rgb)
		exit_error("Failed to split rbg values", data);
	// not leak free
	color = create_trgb(0, check_rgb(rgb[0], data), check_rgb(rgb[1], data),
			check_rgb(rgb[2], data));
	free(rgb);
	return (color);
}

t_img	init_texture_from_config(char *to_find, t_cub3d *data)
{
	char	*line;
	t_img	img;

	ft_memset(&img, 0, sizeof(t_img));
	line = find_in_config(to_find, data->config);
	if (!line)
		exit_error("Missing texture from config file", data);
	line += ft_strlen(to_find);
	img.ptr = mlx_xpm_file_to_image(data->mlx, line, &img.w, &img.h);
	if (!img.ptr)
		exit_error("Loading texture from file", data);
	img.addr = (t_pxl *)mlx_get_data_addr(img.ptr, &img.bpp, &img.lenght,
			&img.end);
	if (!img.addr)
		exit_error("Getting address from image", data);
	return (img);
}
