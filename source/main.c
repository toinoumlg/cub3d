/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/16 13:51:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "logic.h"
#include <X11/Xlib.h>

int	main(int ac, char **av)
{
	t_cub3d	data;

	XInitThreads();
	init_cub3d(&data, ac, av[1]);
	loop(&data);
	free_cub3d(&data);
	return (0);
}
