/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:50:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 20:55:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector3	vector_intersect_plane(t_vector3 plane_p, t_vector3 plane_n,
		t_vector3 line_start, t_vector3 line_end, float *t)
{
	float		plane_d;
	float		ad;
	float		bd;
	t_vector3	line_start_to_end;
	t_vector3	line_to_intersect;

	plane_n = vector_normalize(plane_n);
	plane_d = -vector_dot_product(plane_n, plane_p);
	ad = vector_dot_product(line_start, plane_n);
	bd = vector_dot_product(line_end, plane_n);
	*t = (-plane_d - ad) / (bd - ad);
	line_start_to_end = vector_sub(line_end, line_start);
	line_to_intersect = vector_mul(line_start_to_end, *t);
	return (vector_add(line_start, line_to_intersect));
}

float	dist_point_plane(t_vector3 p, t_vector3 plane_p, t_vector3 plane_n)
{
	return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z
		- vector_dot_product(plane_n, plane_p));
}

int	triange_clipping_against_plane(t_vector3 plane_p, t_vector3 plane_n,
		t_triangle in_tri, t_triangle *out_try1, t_triangle *out_try2)
{
	t_vector3	*inside_points[3];
	t_vector3	*outside_points[3];
	t_vector2	*inside_texture[3];
	t_vector2	*outside_texture[3];
	float		t;
	int			n_inside_points;
	int			n_outside_points;
	int			n_inside_texture;
	int			n_outside_texture;
	float		d0;
	float		d1;
	float		d2;

	n_inside_texture = 0;
	n_outside_texture = 0;
	plane_n = vector_normalize(plane_n);
	n_inside_points = 0;
	n_outside_points = 0;
	d0 = dist_point_plane(in_tri.p[0], plane_p, plane_n);
	d1 = dist_point_plane(in_tri.p[1], plane_p, plane_n);
	d2 = dist_point_plane(in_tri.p[2], plane_p, plane_n);
	if (d0 >= 0)
	{
		inside_points[n_inside_points++] = &in_tri.p[0];
		inside_texture[n_inside_texture++] = &in_tri.t[0];
	}
	else
	{
		outside_points[n_outside_points++] = &in_tri.p[0];
		outside_texture[n_outside_texture++] = &in_tri.t[0];
	}
	if (d1 >= 0)
	{
		inside_points[n_inside_points++] = &in_tri.p[1];
		inside_texture[n_inside_texture++] = &in_tri.t[1];
	}
	else
	{
		outside_points[n_outside_points++] = &in_tri.p[1];
		outside_texture[n_outside_texture++] = &in_tri.t[1];
	}
	if (d2 >= 0)
	{
		inside_points[n_inside_points++] = &in_tri.p[2];
		inside_texture[n_inside_texture++] = &in_tri.t[2];
	}
	else
	{
		outside_points[n_outside_points++] = &in_tri.p[2];
		outside_texture[n_outside_texture++] = &in_tri.t[2];
	}
	if (n_inside_points == 0)
		return (0);
	else if (n_inside_points == 3)
	{
		*out_try1 = in_tri;
		return (1);
	}
	else if (n_inside_points == 1 && n_outside_points == 2)
	{
		out_try1->p[0] = *inside_points[0];
		out_try1->t[0] = *inside_texture[0];
		out_try1->p[1] = vector_intersect_plane(plane_p, plane_n,
				*inside_points[0], *outside_points[0], &t);
		out_try1->t[1].u = t * (outside_texture[0]->u - inside_texture[0]->u)
			+ inside_texture[0]->u;
		out_try1->t[1].v = t * (outside_texture[0]->v - inside_texture[0]->v)
			+ inside_texture[0]->v;
		out_try1->p[2] = vector_intersect_plane(plane_p, plane_n,
				*inside_points[0], *outside_points[1], &t);
		out_try1->t[2].u = t * (outside_texture[1]->u - inside_texture[0]->u)
			+ inside_texture[0]->u;
		out_try1->t[2].v = t * (outside_texture[1]->v - inside_texture[0]->v)
			+ inside_texture[0]->v;
		out_try1->color = create_trgb(0, 125, 125, 255);
		return (1);
	}
	else if (n_inside_points == 2 && n_outside_points == 1)
	{
		out_try1->p[0] = *inside_points[0];
		out_try1->p[1] = *inside_points[1];
		out_try1->t[0] = *inside_texture[0];
		out_try1->t[1] = *inside_texture[1];
		out_try1->p[2] = vector_intersect_plane(plane_p, plane_n,
				*inside_points[0], *outside_points[0], &t);
		out_try1->t[2].u = t * (outside_texture[0]->u - inside_texture[0]->u)
			+ inside_texture[0]->u;
		out_try1->t[2].v = t * (outside_texture[0]->v - inside_texture[0]->v)
			+ inside_texture[0]->v;
		out_try1->color = create_trgb(0, 125, 255, 125);
		out_try2->p[0] = *inside_points[1];
		out_try2->t[0] = *inside_texture[1];
		out_try2->p[1] = out_try1->p[2];
		out_try2->t[1] = out_try1->t[2];
		out_try2->p[2] = vector_intersect_plane(plane_p, plane_n,
				*inside_points[1], *outside_points[0], &t);
		out_try2->t[2].u = t * (outside_texture[0]->u - inside_texture[1]->u)
			+ inside_texture[1]->u;
		out_try1->t[2].v = t * (outside_texture[0]->v - inside_texture[1]->v)
			+ inside_texture[1]->v;
		out_try2->color = create_trgb(0, 255, 0, 255);
		return (2);
	}
	return (-1);
}
