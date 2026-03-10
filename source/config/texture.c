/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:04:29 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 19:13:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "config.h"
#include "cub_utils.h"
#include "graphic.h"
#include "mem.h"
#include "str.h"
#include "swap.h"
#include <stdio.h>

int	check_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	check_rgb(char **split, t_cub3d *data)
{
	int				i;
	int				tmp;
	unsigned char	rgb[3];

	i = 0;
	if (check_size(split) != 3)
	{
		free_array(split);
		exit_error("Invalid rbg value", data);
	}
	while (split[i])
	{
		tmp = -1;
		if (is_nbr(split[i]))
			tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255)
		{
			free_array(split);
			exit_error("Invalid rbg value", data);
		}
		rgb[i++] = tmp;
	}
	return (create_rgb(rgb[0], rgb[1], rgb[2]));
}

int	set_color_from_config(char *to_find, char **config, t_cub3d *data)
{
	char	*line;
	char	**split;
	t_pxl	color;

	line = find_in_config(to_find, config);
	if (!line)
		exit_error("Missing rgb values in config file", data);
	line = skip_whitespace(line + ft_strlen(to_find));
	split = ft_split(line, ',');
	if (!split)
		exit_error("Failed to split rbg values", data);
	color = check_rgb(split, data);
	free_array(split);
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
	line = skip_whitespace(line + ft_strlen(to_find));
	img.ptr = mlx_xpm_file_to_image(data->mlx, line, &img.w, &img.h);
	if (!img.ptr)
		exit_error("Loading texture from file", data);
	img.addr = (t_pxl *)mlx_get_data_addr(img.ptr, &img.bpp, &img.lenght,
			&img.end);
	if (!img.addr)
		exit_error("Getting address from image", data);
	return (img);
}
