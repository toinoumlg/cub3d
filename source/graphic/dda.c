/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:58:26 by amalangu          #+#    #+#             */
/*   Updated: 2026/01/24 00:12:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

static t_vector2	find_step(t_double2 ray_dir)
{
	t_vector2	step;

	if (ray_dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray_dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

static t_double2	find_s_dist(t_double2 player_pos, t_double2 ray_dir,
		t_double2 d_dist)
{
	t_double2	s_dist;

	if (ray_dir.x < 0)
		s_dist.x = (player_pos.x - (int)player_pos.x) * d_dist.x;
	else
		s_dist.x = ((int)player_pos.x + 1 - player_pos.x) * d_dist.x;
	if (ray_dir.y < 0)
		s_dist.y = (player_pos.y - (int)player_pos.y) * d_dist.y;
	else
		s_dist.y = ((int)player_pos.y + 1 - player_pos.y) * d_dist.y;
	return (s_dist);
}

static int	perfom_dda(int **map, t_double2 player_pos, t_vector2 step,
		t_raycaster *rc)
{
	int	side;

	while (1)
	{
		if (rc->s_dist.x < rc->s_dist.y)
		{
			rc->s_dist.x += rc->d_dist.x;
			player_pos.x += step.x;
			side = 0;
		}
		else
		{
			rc->s_dist.y += rc->d_dist.y;
			player_pos.y += step.y;
			side = 1;
		}
		if (map[(int)player_pos.y][(int)player_pos.x] > 0)
			break ;
	}
	return (side);
}

void	find_perp_dist(int **map, t_double2 player_pos, t_raycaster *rc)
{
	t_vector2	step;

	step = find_step(rc->ray_dir);
	rc->s_dist = find_s_dist(player_pos, rc->ray_dir, rc->d_dist);
	rc->side = perfom_dda(map, player_pos, step, rc);
	if (!rc->side)
		rc->perp_dist = (rc->s_dist.x - rc->d_dist.x);
	else
		rc->perp_dist = (rc->s_dist.y - rc->d_dist.y);
}
