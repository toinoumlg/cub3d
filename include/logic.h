/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:05:23 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/13 17:28:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H
# define LOGIC_H

# include "struct.h"

void	loop(t_cub3d *data);
void	rotate(t_double2 *dir, t_double2 *plane, double speed);
void	move(t_double2 *dir, t_cub3d *data, float speed);

#endif