/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:59:36 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 23:26:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_file_content.c
 * @brief Functions to read the .cub file content into memory.
 *
 * This file contains functions to count the number of lines in the .cub file,
 * allocate memory for storing the file content, and read each line into an
 * array of strings for later parsing of textures, colors, and map layout.
 */

#include "cub3d.h"

/**
 * @brief Counts the number of lines in a file.
 *
 * Opens the file at the given path and reads it line by line
 * using get_next_line.
 *
 * @param path Path to the file.
 * @return Number of lines found.
 */
static int	count_file_lines(char *path)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error_msg(path, strerror(errno), errno);
	while (1)
	{
		line = NULL;
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

/**
 * @brief Reads all lines from the opened file descriptor.
 *
 * Stores each line into data->mapinfo.file.
 *
 * @param data Pointer to engine context.
 */
static void	copy_lines(t_engine *data, int fd, int line_count)
{
	char	*line;
	int		i;

	i = 0;
	while (i < line_count)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			data->lines[i++] = line;
			continue ;
		}
		data->lines[i] = ft_strtrim(line, "\n");
		free(line);
		if (!data->lines[i++])
			exit_free(data, NULL, ERROR_MALLOC, FAILURE);
	}
	if (i != line_count)
		exit_free(data, NULL, "Failed reach EOF during copy", FAILURE);
}

/**
 * @brief Loads the entire .cub file into memory.
 *
 * Allocates an array of strings containing each line of the file.
 *
 * @param path Path to the .cub file.
 * @param data Pointer to the engine context.
 */
void	load_file(char *path, t_engine *data)
{
	int	line_count;
	int	fd;

	line_count = count_file_lines(path);
	data->lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!data->lines)
		exit_free(data, NULL, ERROR_MALLOC, FAILURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_free(data, path, strerror(errno), FAILURE);
	copy_lines(data, fd, line_count);
}
