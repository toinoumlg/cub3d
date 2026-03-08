/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:22:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/08 11:27:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H

# include "struct.h"

void		set_timer(t_cub3d *data);
void		get_current_time(t_cub3d *data);
void		free_array(char **array);
int			free_cub3d(t_cub3d *data);
t_vector2	set_vector2(int x, int y);
t_double2	set_double2(float x, float y);
double		ft_abs(double nb);
void		exit_error(char *error, t_cub3d *data);

#endif