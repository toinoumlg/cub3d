/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:04:29 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:36:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "graphic.h"
#include "mem.h"
#include "str.h"
#include "swap.h"

int	pick_color_from_line(char *line, int offset)
{
	int	color;

	while (offset)
	{
		while (line && !(*line >= '0' && *line <= '9'))
			line++;
		if (!line)
			return (-1);
		while (*line >= '0' && *line <= '9')
			line++;
		offset--;
	}
	while (line && !(*line >= '0' && *line <= '9'))
		line++;
	if (!line)
		return (-1);
	color = ft_atoi(line);
	if (color > 255 || color < 0)
		return (-1);
	return (color);
}

int	set_color_from_config(char *to_find, char **config, t_cub3d *data)
{
	int				color;
	unsigned char	rgb[3];
	int				tmp;
	int				i;
	char			*line;

	i = -1;
	line = find_in_config(to_find, config);
	if (!line)
		exit_error("Missing rbg values in config file", data);
	line += ft_strlen(to_find);
	while (++i < 3)
	{
		tmp = pick_color_from_line(line, i);
		if (tmp == -1)
			exit_error("Wrong value for rbg colors", data);
		rgb[i] = tmp;
	}
	color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
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
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lenght, &img.end);
	return (img);
}
