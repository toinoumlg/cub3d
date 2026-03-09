/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:04:09 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/09 14:15:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "mem.h"
#include "str.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen_with_tab(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\t')
			size += 4;
		else
			size++;
		i++;
	}
	return (size);
}

char	*find_in_config(char *to_find, char **config)
{
	bool	found;
	char	*tmp;

	found = false;
	tmp = NULL;
	while (*config)
	{
		if (map_line(*config))
			return (tmp);
		if (!ft_strncmp(to_find, *config, ft_strlen(to_find)))
		{
			if (found)
				return (NULL);
			tmp = *config;
			found = true;
		}
		config++;
	}
	return (tmp);
}

static int	file_size(int fd)
{
	char	*tmp;
	int		line_nbr;

	line_nbr = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line_nbr++;
		free(tmp);
	}
	close(fd);
	return (line_nbr);
}

int	try_open(char *config)
{
	int		fd;
	char	*cub;

	fd = open(config, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		exit_error("Input file is a directory", NULL);
	}
	cub = ft_strnstr(config, ".cub", ft_strlen(config));
	if (!config || !cub || ft_strncmp(cub, ".cub", 5))
		exit_error("No map file or invalid extension", NULL);
	fd = open(config, O_RDONLY);
	if (fd < 0)
		exit_error("Wrong config file name", NULL);
	return (file_size(fd));
}

void	copy_config(int size, char *file, t_cub3d *data)
{
	int		i;
	char	*tmp;

	i = 0;
	allocate_config(size, data);
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		exit_error("Failed to open config file", data);
	while (i < size)
	{
		tmp = get_next_line(data->fd);
		if (!tmp)
			exit_error("Allocation failed during config copy", data);
		if (*tmp == '\n')
		{
			data->config[i++] = tmp;
			continue ;
		}
		data->config[i] = ft_strtrim(tmp, "\n");
		free(tmp);
		if (!data->config[i++])
			exit_error("Allocation failed during trim of config", data);
	}
}
