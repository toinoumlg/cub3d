/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:03:34 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/20 14:55:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "struct.h"

void	init_cub3d(t_cub3d *data, int ac, char **av);
t_img	init_texture_from_config(char *to_find, t_cub3d *data);
int		set_color_from_config(char *to_find, char **config, t_cub3d *data);
void	copy_config(int size, char *file, t_cub3d *data);
int		try_open(char *config);
char	*find_in_config(char *to_find, char **config);
int		ft_strlen_with_tab(char *str);
void	allocate_config(int size, t_cub3d *data);
void	alloc_map(t_cub3d *data);
void	flood_fill(int x, int y, t_vector2 map_size, t_cub3d *data);
void	restore_map(int **map, t_vector2 map_size);
void	parse_config(t_cub3d *data);
void	load_map(char **config, t_cub3d *data);

#endif