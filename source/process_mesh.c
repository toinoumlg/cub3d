/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_mesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:52:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:40:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"

void	draw_triangle_to_image(t_triangle projected, t_cub3d *data, int color)
{
	draw_line(projected.p[0].x, projected.p[0].y, projected.p[1].x,
		projected.p[1].y, data, color, projected.p[0].z);
	draw_line(projected.p[1].x, projected.p[1].y, projected.p[2].x,
		projected.p[2].y, data, color, projected.p[0].z);
	draw_line(projected.p[2].x, projected.p[2].y, projected.p[0].x,
		projected.p[0].y, data, color, projected.p[0].z);
}

void	swap_vector(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void	sort_vector(t_triangle *projected)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = i;
		while (++j < 3)
		{
			if (projected->p[i].y > projected->p[j].y)
				swap_vector(&projected->p[i], &projected->p[j]);
		}
		i++;
	}
}

int	*interpolate(int xmin, int ymin, int xmax, int ymax, int *count)
{
	int		*arr;
	int		dy;
	int		i;
	float	tmp;

	if (ymin == ymax)
	{
		*count = 1;
		arr = malloc(sizeof(int));
		arr[0] = xmin;
		return (arr);
	}
	dy = ymax - ymin;
	*count = dy + 1;
	i = 0;
	arr = malloc(*count * sizeof(int));
	while (i <= dy)
	{
		tmp = (float)i / (float)dy;
		arr[i++] = (float)xmin + tmp * ((float)xmax - (float)xmin);
	}
	return (arr);
}

int	*interpolate_both(t_triangle projected, int *count)
{
	int	*x01;
	int	*x12;
	int	*arr;
	int	count12;
	int	count01;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x01 = interpolate((int)projected.p[0].x, (int)projected.p[0].y,
			(int)projected.p[1].x, (int)projected.p[1].y, &count01);
	x12 = interpolate((int)projected.p[1].x, (int)projected.p[1].y,
			(int)projected.p[2].x, (int)projected.p[2].y, &count12);
	*count = count01 + count12 - 1;
	arr = malloc(sizeof(int) * (count01 + count12 - 1));
	while (i < count01 - 1)
	{
		arr[i] = x01[i];
		i++;
	}
	while (j < count12)
	{
		arr[i + j] = x12[j];
		j++;
	}
	free(x01);
	free(x12);
	return (arr);
}

void	fill(int *x_left, int *x_right, t_triangle projected, t_cub3d *data,
		int color)
{
	int	y;
	int	x_left_value;
	int	x_right_value;

	y = projected.p[0].y;
	while (y < projected.p[2].y)
	{
		x_left_value = x_left[y - (int)projected.p[0].y];
		x_right_value = x_right[y - (int)projected.p[0].y];
		draw_horizontal_line(x_left_value, x_right_value, y, data, color,
			projected.p[0].z);
		y++;
	}
}

void	draw_filled_triangle_to_image(t_triangle projected, t_cub3d *data,
		int color)
{
	int	*x02;
	int	*x012;
	int	count;
	int	m;

	sort_vector(&projected);
	x02 = interpolate((int)projected.p[0].x, (int)projected.p[0].y,
			(int)projected.p[2].x, (int)projected.p[2].y, &count);
	x012 = interpolate_both(projected, &count);
	m = floor(count / 2);
	if (x02[m] < x012[m])
		fill(x02, x012, projected, data, color);
	else
		fill(x012, x02, projected, data, color);
	free(x02);
	free(x012);
}

t_mat4x4	construct_wolrd_mat(t_cub3d *data)
{
	t_mat4x4	trans;
	t_mat4x4	world;
	t_mat4x4	rot_z;
	t_mat4x4	rot_x;

	(void)data;
	rot_z = matrix_make_rotation_z(data->timer.time);
	rot_x = matrix_make_rotation_x(data->timer.time);
	trans = matrix_make_translation(0.0f, 0.0f, 15.0f);
	world = matrix_make_idendity();
	world = matrix_multiply_matrix(rot_z, rot_x);
	world = matrix_multiply_matrix(world, trans);
	return (world);
}

t_vector3	get_line_normal(t_triangle tri)
{
	t_vector3	normal;
	t_vector3	line1;
	t_vector3	line2;

	line1 = vector_sub(tri.p[1], tri.p[0]);
	line2 = vector_sub(tri.p[2], tri.p[0]);
	normal = vector_cross_product(line1, line2);
	normal = vector_normalize(normal);
	return (normal);
}

t_triangle	offset_and_set_in_vp(t_vector3 offset, t_triangle tri_projected)
{
	tri_projected.p[0] = vector_add(tri_projected.p[0], offset);
	tri_projected.p[1] = vector_add(tri_projected.p[1], offset);
	tri_projected.p[2] = vector_add(tri_projected.p[2], offset);
	tri_projected.p[0].x *= 0.5f * WINDOW_WIDTH;
	tri_projected.p[0].y *= 0.5f * WINDOW_HEIGHT;
	tri_projected.p[1].x *= 0.5f * WINDOW_WIDTH;
	tri_projected.p[1].y *= 0.5f * WINDOW_HEIGHT;
	tri_projected.p[2].x *= 0.5f * WINDOW_WIDTH;
	tri_projected.p[2].y *= 0.5f * WINDOW_HEIGHT;
	return (tri_projected);
}

t_mat4x4	matrix_point_at(t_vector3 pos, t_vector3 target, t_vector3 up)
{
	t_vector3	new_fwd;
	t_vector3	a;
	t_vector3	new_up;
	t_vector3	new_r;
	t_mat4x4	matrix;

	new_fwd = vector_sub(target, pos);
	new_fwd = vector_normalize(new_fwd);
	a = vector_mul(new_fwd, vector_dot_product(up, new_fwd));
	new_up = vector_sub(up, a);
	new_up = vector_normalize(new_up);
	new_r = vector_cross_product(new_up, new_fwd);
	matrix.mat[0][0] = new_r.x;
	matrix.mat[1][0] = new_up.x;
	matrix.mat[2][0] = new_fwd.x;
	matrix.mat[3][0] = pos.x;
	matrix.mat[0][1] = new_r.y;
	matrix.mat[1][1] = new_up.y;
	matrix.mat[2][1] = new_fwd.y;
	matrix.mat[3][1] = pos.y;
	matrix.mat[0][2] = new_r.z;
	matrix.mat[1][2] = new_up.z;
	matrix.mat[2][2] = new_fwd.z;
	matrix.mat[3][2] = pos.z;
	matrix.mat[0][3] = 0.0f;
	matrix.mat[1][3] = 0.0f;
	matrix.mat[2][3] = 0.0f;
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

t_mat4x4	matrix_look_at(t_mat4x4 m)
{
	t_mat4x4	matrix;

	matrix.mat[0][0] = m.mat[0][0];
	matrix.mat[0][1] = m.mat[1][0];
	matrix.mat[0][2] = m.mat[2][0];
	matrix.mat[0][3] = 0.0f;
	matrix.mat[1][0] = m.mat[0][1];
	matrix.mat[1][1] = m.mat[1][1];
	matrix.mat[1][2] = m.mat[2][1];
	matrix.mat[1][3] = 0.0f;
	matrix.mat[2][0] = m.mat[0][2];
	matrix.mat[2][1] = m.mat[1][2];
	matrix.mat[2][2] = m.mat[2][2];
	matrix.mat[2][3] = 0.0f;
	matrix.mat[3][0] = -(m.mat[3][0] * matrix.mat[0][0] + m.mat[3][1]
			* matrix.mat[1][0] + m.mat[3][2] * matrix.mat[2][0]);
	matrix.mat[3][1] = -(m.mat[3][0] * matrix.mat[0][1] + m.mat[3][1]
			* matrix.mat[1][1] + m.mat[3][2] * matrix.mat[2][1]);
	matrix.mat[3][2] = -(m.mat[3][0] * matrix.mat[0][2] + m.mat[3][1]
			* matrix.mat[1][2] + m.mat[3][2] * matrix.mat[2][2]);
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

void	push_back(t_triangle **list, t_triangle new_t)
{
	t_triangle	*tmp;
	t_triangle	*new_raster;

	new_raster = malloc(sizeof(t_triangle));
	*new_raster = new_t;
	new_raster->next = NULL;
	if (!*list)
	{
		*list = new_raster;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_raster;
}

void	pop_front(t_triangle **list)
{
	t_triangle	*tmp;

	if (!*list)
		return ;
	tmp = *list;
	*list = tmp->next;
	free(tmp);
}

int	list_size(t_triangle *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	process_mesh(t_cub3d *data)
{
	t_triangle	*try_to_raster;
	t_triangle	*clipped_against_screen_edge;
	t_triangle	*mesh;
	t_mat4x4	world;
	t_vector3	v_up;
	t_vector3	v_target;
	t_mat4x4	rot;
	t_mat4x4	camera;
	t_mat4x4	view;
	t_triangle	tri_projected;
	t_triangle	tri_transformed;
	t_triangle	tri_view;
	t_vector3	normal;
	t_vector3	camera_ray;
	t_vector3	light_direction;
	float		dp;
	int			n_clipped_triangle;
	t_triangle	clipped[2];
	int			n;
	t_vector3	offset;
	t_triangle	*next;
	t_triangle	*next2;
	int			n_new_triangle;
	int			p;
	int			n_tri_to_add;
	t_triangle	test;
	int			w;

	clipped_against_screen_edge = NULL;
	try_to_raster = NULL;
	mesh = data->object.mesh;
	world = construct_wolrd_mat(data);
	v_up = set_vector3(0, 1, 0);
	v_target = set_vector3(0, 0, 1);
	rot = matrix_make_rotation_y(data->yaw);
	data->look_dir = matrix_multiply_vector(rot, v_target);
	v_target = vector_add(data->camera, data->look_dir);
	camera = matrix_point_at(data->camera, v_target, v_up);
	view = matrix_look_at(camera);
	while (mesh)
	{
		tri_transformed = *mesh;
		tri_transformed = matrix_multiply_triangle(world, *mesh);
		normal = get_line_normal(tri_transformed);
		camera_ray = vector_sub(tri_transformed.p[0], data->camera);
		if (vector_dot_product(normal, camera_ray) < 0.0f)
		{
			light_direction = set_vector3(0.0f, 0.0f, -1.0f);
			light_direction = vector_normalize(light_direction);
			dp = vector_dot_product(light_direction, normal);
			tri_view = matrix_multiply_triangle(view, tri_transformed);
			tri_view.color = mesh->color;
			n_clipped_triangle = 0;
			n_clipped_triangle = triange_clipping_against_plane(set_vector3(0,
						0, 0.1f), set_vector3(0, 0, 1.0f), tri_view,
					&clipped[0], &clipped[1]);
			n = 0;
			while (n < n_clipped_triangle)
			{
				// 3D => 2D
				tri_projected = matrix_multiply_triangle(data->proj,
						clipped[n++]);
				tri_projected.p[0].x *= -1.0f;
				tri_projected.p[1].x *= -1.0f;
				tri_projected.p[2].x *= -1.0f;
				tri_projected.p[0].y *= -1.0f;
				tri_projected.p[1].y *= -1.0f;
				tri_projected.p[2].y *= -1.0f;
				offset = set_vector3(1.0f, 1.0f, 0.0f);
				tri_projected = offset_and_set_in_vp(offset, tri_projected);
				push_back(&try_to_raster, tri_projected);
			}
		}
		mesh = mesh->next;
	}
	while (try_to_raster)
	{
		next = try_to_raster->next;
		push_back(&clipped_against_screen_edge, *try_to_raster);
		n_new_triangle = 1;
		p = 0;
		while (p < 4)
		{
			n_tri_to_add = 0;
			while (n_new_triangle > 0)
			{
				test = *clipped_against_screen_edge;
				pop_front(&clipped_against_screen_edge);
				n_new_triangle--;
				if (p == 0)
					n_tri_to_add = triange_clipping_against_plane(set_vector3(0,
								0, 0), set_vector3(0, 1.0f, 0), test,
							&clipped[0], &clipped[1]);
				if (p == 1)
					n_tri_to_add = triange_clipping_against_plane(set_vector3(0,
								(float)WINDOW_HEIGHT - 1, 0), set_vector3(0,
								-1.0f, 0), test, &clipped[0], &clipped[1]);
				if (p == 2)
					n_tri_to_add = triange_clipping_against_plane(set_vector3(0,
								0, 0), set_vector3(1.0f, 0, 0), test,
							&clipped[0], &clipped[1]);
				if (p == 3)
					n_tri_to_add = triange_clipping_against_plane(set_vector3((float)WINDOW_WIDTH
								- 1, 0, 0), set_vector3(-1.0f, 0, 0), test,
							&clipped[0], &clipped[1]);
				w = 0;
				while (w < n_tri_to_add)
					push_back(&clipped_against_screen_edge, clipped[w++]);
			}
			n_new_triangle = list_size(clipped_against_screen_edge);
			p++;
		}
		while (clipped_against_screen_edge)
		{
			next2 = clipped_against_screen_edge->next;
			draw_filled_triangle_to_image(*clipped_against_screen_edge, data,
				clipped_against_screen_edge->color);
			// draw_triangle_to_image(*clipped_against_screen_edge, data,
			// 	create_trgb(0, 255, 255, 255));
			draw_texture(clipped_against_screen_edge->p[0].x,
							clipped_against_screen_edge->p[0].y,
							clipped_against_screen_edge->t[0].u,
							clipped_against_screen_edge->t[0].v,
							clipped_against_screen_edge->p[1].x,
							clipped_against_screen_edge->p[1].y,
							clipped_against_screen_edge->t[1].u,
							clipped_against_screen_edge->t[1].v,
							clipped_against_screen_edge->p[2].x,
							clipped_against_screen_edge->p[2].y,
							clipped_against_screen_edge->t[2].u,
							clipped_against_screen_edge->t[2].v,
							&data->object.texture,
							data,
							clipped_against_screen_edge->p[0].z);
			free(clipped_against_screen_edge);
			clipped_against_screen_edge = next2;
		}
		free(try_to_raster);
		try_to_raster = next;
	}
	(void)dp;
}
