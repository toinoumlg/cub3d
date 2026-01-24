/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 12:56:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "cub_utils.h"
#include "logic.h"

int	main(int ac, char **av)
{
	t_cub3d	data;

	init_cub3d(&data, ac, av[1]);
	loop(&data);
	free_cub3d(&data);
	return (0);
}
