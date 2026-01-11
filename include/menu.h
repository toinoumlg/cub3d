/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:12:49 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/11 08:55:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "cub3d.h"
# include "utils.h"

typedef struct s_button
{
	t_int2		pos;
	t_int2		size;
	int			color;
}				t_button;

typedef struct s_menu
{
	t_int2		mouse;
	t_img		img;
	t_button	start;
}				t_menu;

#endif