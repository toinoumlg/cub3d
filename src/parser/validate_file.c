/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:51:18 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 15:48:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_file.c
 * @brief Functions to validate input files
 * (.cub and .xpm) for cub3D.
 */
#include "cub3d.h"

/**
 * @brief Checks if the given path corresponds to a directory.
 *
 * @param path The file path to check.
 * @return true if path is a directory, false otherwise.
 */
static bool	is_directory(char *path)
{
	int		fd;
	bool	ret_value;

	ret_value = false;
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ret_value = true;
	}
	return (ret_value);
}

/**
 * @brief Validates a file by checking its existence, type, and extension.
 *
 * This function verifies:
 * 1. The file exists and is not a directory.
 * 2. The file can be opened for reading.
 * 3. The file has the correct extension
 * (".cub" if cub is true, ".xpm" if false).
 *
 * @param path Path to the file to validate.
 * @param cub Boolean indicating whether the file should be
 * a .cub file (true) or a .xpm file (false).
 * @return SUCCESS if the file is valid, FAILURE otherwise
 * (prints an error message).
 */
void	validate_file(char *path)
{
	int	fd;

	if (is_directory(path))
	{
		print_error_msg(path, ERROR_FILE_IS_DIR, FAILURE);
		exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error_msg(path, strerror(errno), FAILURE);
		exit(1);
	}
	close(fd);
	if (ft_strncmp(ft_strnstr(path, ".cub", ft_strlen(path)), ".cub", 5))
	{
		print_error_msg(path, ERROR_FILE_NOT_CUB, FAILURE);
		exit(1);
	}
}
