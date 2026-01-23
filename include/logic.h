/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:05:23 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/23 23:57:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H
# define LOGIC_H

# include "struct.h"

void	loop(t_cub3d *data);
void	rotate(t_double2 *dir, t_double2 *plane, float direction,
			double d_time);
void	move(t_double2 *dir, t_cub3d *data, int direction);
void	apply_motion(t_cub3d *data);
int		key_released(int key, t_cub3d *data);
int		key_pressed(int key, t_cub3d *data);
#endif