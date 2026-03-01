/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:36:02 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 22:43:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_config.c
 * @brief Main configuration file parsing functions for the cub3D engine.
 *

	* This file contains the main logic to read the configuration file line by line,
 * extract texture paths, floor and ceiling colors, and map layout. It ensures
 * that the configuration is valid and properly stored in the engine's data
 * structures for later use in rendering and game logic.
 */

#include "cub3d.h"

char	*find_line(char **lines, char *to_find)
{
	int		i;
	int		count;
	char	*found;
	int		len;

	found = NULL;
	len = ft_strlen(to_find);
	i = 0;
	count = 0;
	while (lines[i])
	{
		if (!ft_strncmp(to_find, lines[i], len))
		{
			count++;
			if (count > 1)
				return (NULL);
			found = lines[i];
		}
		i++;
	}
	return (found);
}

t_image	init_texture_from_line(char *to_find, t_engine *data)
{
	char	*line;
	t_image	img;

	ft_memset(&img, 0, sizeof(t_image));
	line = find_line(data->lines, to_find);
	if (!line)
		exit_free(data, NULL, "Duplicate texture idientifier or none", FAILURE);
	line += ft_strlen(to_find);
	img.ptr = mlx_xpm_file_to_image(data->mlx, line, &img.w, &img.h);
	if (!img.ptr)
		exit_free(data, NULL, "Invalid xmp image", FAILURE);
	img.addr = (int *)mlx_get_data_addr(img.ptr, &img.pixel_bits,
			&img.size_line, &img.endian);
	if (!img.addr)
		exit_free(data, NULL, "Failed to get image", FAILURE);
	return (img);
}

int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char[4]){b, g, r, 0});
}

int	check_rgb(char **split, t_engine *data)
{
	int				i;
	int				tmp;
	unsigned char	rgb[3];

	i = 0;
	while (split[i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255 || i > 2)
		{
			free_2d_array((void **)split);
			exit_free(data, NULL, "Invalid color size for an rgb value",
				FAILURE);
		}
		rgb[i++] = tmp;
	}
	return (create_rgb(rgb[0], rgb[1], rgb[2]));
}

int	set_color_from_file(char *to_find, t_engine *data)
{
	char	*line;
	char	**split;
	int		color;

	line = find_line(data->lines, to_find);
	if (!line)
		exit_free(data, NULL, "Duplicate color for ceiling/Floor or none",
			FAILURE);
	line += ft_strlen(to_find);
	split = ft_split(line, ',');
	if (!split)
		exit_free(data, NULL, "Failed to split RBG values", FAILURE);
	color = check_rgb(split, data);
	free_2d_array((void **)split);
	return (color);
}

int	is_map_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!is_blank(*str) && *str != '0' && *str != '1' && *str != 'N'
			&& *str != 'E' && *str != 'S' && *str != 'W')
			return (0);
		str++;
	}
	return (1);
}

int	is_blank_line(char *str)
{
	while (*str)
		if (is_blank(*str++))
			return (1);
	return (0);
}

void	check_remaining(char **lines, t_engine *data)
{
	while (*lines)
		if (is_blank_line(*lines++))
			exit_free(data, NULL, "Invalid character after the end of map",
				FAILURE);
}

void	get_map_size(char **lines, t_vector2 *size, t_engine *data)
{
	int	tmp;

	while (*lines)
	{
		if (!is_map_line(*lines) || **lines == '\n')
			break ;
		tmp = ft_strlen(*lines);
		if (tmp > size->x)
			size->x = tmp;
		size->y++;
		lines++;
	}
	check_remaining(lines, data);
}

void	copy_map(char **lines, t_engine *data)
{
	int	i;

	i = 0;
	get_map_size(lines, &data->map_size, data);
	data->map = ft_calloc(data->map_size.y + 1, sizeof(char *));
	while (i < data->map_size.y)
	{
		data->map[i] = ft_calloc(data->map_size.x + 1, sizeof(char));
		if (!data->map[i])
			exit_free(data, NULL, "Failed to duplicate map row", FAILURE);
		ft_memcpy(data->map[i], lines[i], ft_strlen(lines[i]));
		i++;
	}
}

void	load_map(char **lines, t_engine *data)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (copy_map(lines + i, data));
		i++;
	}
	exit_free(data, NULL, "No map found in config", FAILURE);
}

/**
 * @brief Parses the entire configuration file.
 *
 * Reads textures, colors, and map data in order.
 *
 * @param data Main data structure.
 * @param file File content.
 * @return SUCCESS or FAILURE.
 */
void	get_config(t_engine *data)
{
	data->floor = set_color_from_file("F ", data);
	data->ceiling = set_color_from_file("C ", data);
	data->textures[NORTH] = init_texture_from_line("NO ", data);
	data->textures[SOUTH] = init_texture_from_line("SO ", data);
	data->textures[WEST] = init_texture_from_line("WE ", data);
	data->textures[EAST] = init_texture_from_line("EA ", data);
	load_map(data->lines, data);
	// print_map(data->map);
}
