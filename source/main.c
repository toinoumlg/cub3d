/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:57:59 by amalangu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/20 15:10:20 by amalangu         ###   ########.fr       */
=======
/*   Updated: 2026/01/22 12:46:16 by amalangu         ###   ########.fr       */
>>>>>>> origin/main
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
