/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:59:55 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:10:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"

t_vector3	matrix_multiply_vector(t_mat4x4 m, t_vector3 in)
{
	t_vector3	out;

	ft_memset(&out, 0, sizeof(t_vector3));
	out.x = in.x * m.mat[0][0] + in.y * m.mat[1][0] + in.z * m.mat[2][0]
		+ m.mat[3][0];
	out.y = in.x * m.mat[0][1] + in.y * m.mat[1][1] + in.z * m.mat[2][1]
		+ m.mat[3][1];
	out.z = in.x * m.mat[0][2] + in.y * m.mat[1][2] + in.z * m.mat[2][2]
		+ m.mat[3][2];
	out.w = in.x * m.mat[0][3] + in.y * m.mat[1][3] + in.z * m.mat[2][3]
		+ m.mat[3][3];
	if (out.w != 0.0f)
		out = vector_div(out, out.w);
	return (out);
}

t_triangle	matrix_multiply_triangle(t_mat4x4 m, t_triangle in)
{
	t_triangle	out;

	ft_memset(&out, 0, sizeof(t_triangle));
	out.p[0] = matrix_multiply_vector(m, in.p[0]);
	out.p[1] = matrix_multiply_vector(m, in.p[1]);
	out.p[2] = matrix_multiply_vector(m, in.p[2]);
	out.t[0] = in.t[0];
	out.t[1] = in.t[1];
	out.t[2] = in.t[2];
	out.color = in.color;
	return (out);
}

t_mat4x4	matrix_make_idendity(void)
{
	t_mat4x4	matrix;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	matrix.mat[0][0] = 1.0f;
	matrix.mat[1][1] = 1.0f;
	matrix.mat[2][2] = 1.0f;
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

t_mat4x4	matrix_make_rotation_x(float angle_rad)
{
	t_mat4x4	matrix;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	matrix.mat[0][0] = 1.0f;
	matrix.mat[1][1] = cosf(angle_rad);
	matrix.mat[1][2] = sinf(angle_rad);
	matrix.mat[2][1] = -sinf(angle_rad);
	matrix.mat[2][2] = cosf(angle_rad);
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

t_mat4x4	matrix_make_rotation_y(float angle_rad)
{
	t_mat4x4	matrix;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	matrix.mat[0][0] = cosf(angle_rad);
	matrix.mat[0][2] = sinf(angle_rad);
	matrix.mat[2][0] = -sinf(angle_rad);
	matrix.mat[1][1] = 1.0f;
	matrix.mat[2][2] = cosf(angle_rad);
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

t_mat4x4	matrix_make_rotation_z(float angle_rad)
{
	t_mat4x4	matrix;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	matrix.mat[0][0] = cosf(angle_rad);
	matrix.mat[0][1] = sinf(angle_rad);
	matrix.mat[1][0] = -sinf(angle_rad);
	matrix.mat[1][1] = cosf(angle_rad);
	matrix.mat[2][2] = 1.0f;
	matrix.mat[3][3] = 1.0f;
	return (matrix);
}

t_mat4x4	matrix_make_translation(float x, float y, float z)
{
	t_mat4x4	matrix;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	matrix.mat[0][0] = 1.0f;
	matrix.mat[1][1] = 1.0f;
	matrix.mat[2][2] = 1.0f;
	matrix.mat[3][3] = 1.0f;
	matrix.mat[3][0] = x;
	matrix.mat[3][1] = y;
	matrix.mat[3][2] = z;
	return (matrix);
}

t_mat4x4	matrix_make_projection(void)
{
	t_mat4x4	matrix;
	float		aspect_ratio;
	float		fov_rad;

	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	fov_rad = 1.0f / tanf(FFOV * 0.5f / 180.0f * 3.14159f);
	aspect_ratio = WINDOW_HEIGHT / WINDOW_WIDTH;
	matrix.mat[0][0] = aspect_ratio * fov_rad;
	matrix.mat[1][1] = fov_rad;
	matrix.mat[2][2] = FFAR / (FFAR - FNEAR);
	matrix.mat[3][2] = (-FFAR * FNEAR) / (FFAR - FNEAR);
	matrix.mat[2][3] = 1.0f;
	matrix.mat[3][3] = 0.0f;
	return (matrix);
}

t_mat4x4	matrix_multiply_matrix(t_mat4x4 m1, t_mat4x4 m2)
{
	t_mat4x4 matrix;

	int c = 0;
	int r;
	ft_memset(&matrix, 0, sizeof(t_mat4x4));
	while (c < 4)
	{
		r = 0;
		while (r < 4)
		{
			matrix.mat[r][c] = m1.mat[r][0] * m2.mat[0][c] + m1.mat[r][1]
				* m2.mat[1][c] + m1.mat[r][2] * m2.mat[2][c] + m1.mat[r][3]
				* m2.mat[3][c];
			r++;
		}
		c++;
	}
	return (matrix);
}