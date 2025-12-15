/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:05:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/12/15 13:06:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "cub3d.h"

void	rotate(t_double2 *dir, t_double2 *plane, double speed);
void	move_fwd(t_double2 *dir, t_double2 *pos, int **map, t_double2 map_size);
void	move_bwd(t_double2 *dir, t_double2 *pos, int **map, t_double2 map_size);
void	move_left(t_double2 *dir, t_double2 *pos, int **map,
			t_double2 map_size);
void	move_right(t_double2 *dir, t_double2 *pos, int **map,
			t_double2 map_size);

#endif