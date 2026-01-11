/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:30 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/11 09:00:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "str.h"
#include <fcntl.h>
#include <unistd.h>

t_img	new_image(void *mlx)
{
	t_img	new_img;

	new_img.ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	new_img.addr = mlx_get_data_addr(new_img.ptr, &new_img.bpp, &new_img.lenght,
			&new_img.end);
	return (new_img);
}

t_double2	get_map_size(char *file_name)
{
	t_double2	map_size;
	int			fd;
	char		*str;
	char		*trim;
	int			tmp;

	map_size = set_double2(0.0, -1.0);
	fd = open(file_name, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		trim = ft_strtrim(str, "\n");
		free(str);
		map_size.y++;
		tmp = map_size.x;
		map_size.x = ft_strlen(trim);
		if (tmp > map_size.x)
			map_size.x = tmp;
		free(trim);
	}
	close(fd);
	map_size.x--;
	return (map_size);
}

int	*copy_line(char *str, int len)
{
	int	i;
	int	*row;

	i = 0;
	row = malloc(sizeof(int) * len);
	while (i < len)
	{
		row[i] = str[i] - '0';
		i++;
	}
	return (row);
}

void	init_fake_map(char *file_name, t_cub3d *data)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	data->map_size = get_map_size(file_name);
	fd = open(file_name, O_RDONLY);
	data->map = malloc(sizeof(int *) * data->map_size.y);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			return ;
		data->map[i++] = copy_line(str, ft_strlen(str));
		free(str);
	}
}

void	init_menu(t_menu *menu)
{
	menu->start.pos = set_int2(WINDOW_WIDTH / 2 - WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / 100);
	menu->start.size = set_int2(200, 20);
}

void	init_data(t_cub3d *data)
{
	set_timer(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	data->buffer = new_image(data->mlx);
	data->menu.img = new_image(data->mlx);
	data->plane = set_double2(0.0, 0.66);
	data->player.pos = set_double2(22.0, 12.0);
	data->player.dir = set_double2(-1.1, 0.0);
	init_fake_map("map.txt", data);
	init_menu(&data->menu);
}
