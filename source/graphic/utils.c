/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:29:14 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/10 14:37:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "graphic.h"
#include "struct.h"

t_pxl	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, 0});
}

void	set_minimap_max_value(t_vector2 *hit_minimap, t_minimap *minimap)
{
	if (hit_minimap->x < 0)
		hit_minimap->x = 0;
	if (hit_minimap->x >= minimap->buffer.w)
		hit_minimap->x = minimap->buffer.w - 1;
	if (hit_minimap->y < 0)
		hit_minimap->y = 0;
	if (hit_minimap->y >= minimap->buffer.h)
		hit_minimap->y = minimap->buffer.h - 1;
}

t_vector2	get_hit_pos_on_minimap(t_raycaster *rc, t_double2 *player_pos,
		t_minimap *minimap)
{
	t_double2	hit_map;
	t_vector2	hit_minimap;

	hit_map.x = player_pos->x + rc->perp_dist * rc->ray_dir.x;
	hit_map.y = player_pos->y + rc->perp_dist * rc->ray_dir.y;
	hit_minimap.x = (hit_map.x - minimap->offset.x) * MINI_MAP_SCALE;
	hit_minimap.y = (hit_map.y - minimap->offset.y) * MINI_MAP_SCALE;
	return (hit_minimap);
}
