/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:05:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:25:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_swap_f(float *f1, float *f2)
{
	float	tmp;

	tmp = *f1;
	*f1 = *f2;
	*f2 = tmp;
}

int	get_color(float u, float v, t_img *texture)
{
	int	x;
	int	y;

	x = (int)(u * texture->w);
	y = (int)(v * texture->h);
	if (x < 0 || x >= texture->w || y < 0 || y >= texture->h)
		return (0);
	return (*(int *)(texture->addr + (y * texture->lenght + x * (texture->bpp
					/ 8))));
}

void	draw_texture(int x1, int y1, float u1, float v1, int x2, int y2,
		float u2, float v2, int x3, int y3, float u3, float v3, t_img *texture,
		t_cub3d *data, float z)
{
	if (y2 < y1)
	{
		ft_swap(&y1, &y2);
		ft_swap(&x1, &x2);
		ft_swap_f(&u1, &u2);
		ft_swap_f(&v1, &v2);
	}
	if (y3 < y1)
	{
		ft_swap(&y1, &y3);
		ft_swap(&x1, &x3);
		ft_swap_f(&u1, &u3);
		ft_swap_f(&v1, &v3);
	}
	if (y3 < y2)
	{
		ft_swap(&y2, &y3);
		ft_swap(&x2, &x3);
		ft_swap_f(&u2, &u3);
		ft_swap_f(&v2, &v3);
	}
	int dy1 = y2 - y1;
	int dx1 = x2 - x1;
	float dv1 = v2 - v1;
	float du1 = u2 - u1;
	int dy2 = y3 - y1;
	int dx2 = x3 - x1;
	float dv2 = v3 - v1;
	float du2 = u3 - u1;
	float tex_u, tex_v;
	float dax_step = 0, dbx_step = 0, du1_step = 0, dv1_step = 0, du2_step = 0,
		dv2_step = 0;
	if (dy1)
		dax_step = dx1 / (float)ft_abs(dy1);
	if (dy2)
		dbx_step = dx2 / (float)ft_abs(dy2);

	if (dy1)
		du1_step = du1 / (float)ft_abs(dy1);
	if (dy1)
		dv1_step = dv1 / (float)ft_abs(dy1);

	if (dy2)
		du2_step = du2 / (float)ft_abs(dy2);
	if (dy2)
		dv2_step = dv2 / (float)ft_abs(dy2);
	int i;
	int j;
	float t_step;
	float t;
	if (dy1)
	{
		i = y1;
		while (i <= y2)
		{
			int ax = x1 + (float)(i - y1) * dax_step;
			int bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u1 + (float)(i - y1) * du1_step;
			float tex_sv = v1 + (float)(i - y1) * dv1_step;
			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			if (ax > bx)
			{
				ft_swap(&ax, &bx);
				ft_swap_f(&tex_su, &tex_eu);
				ft_swap_f(&tex_sv, &tex_ev);
			}
			tex_u = tex_su;
			tex_v = tex_sv;
			t_step = 1.0f / ((float)(bx - ax));
			t = 0.0f;
			j = ax;
			while (j < bx)
			{
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				pxl_put(data, j, i, get_color(tex_u, tex_v, texture), z);
				j++;
				t += t_step;
			}

			i++;
		}
	}
	dy1 = y3 - y2;
	dx1 = x3 - x2;
	dv1 = v3 - v2;
	du1 = u3 - u2;

	if (dy1)
		dax_step = dx1 / (float)ft_abs(dy1);
	if (dy2)
		dbx_step = dx2 / (float)ft_abs(dy2);

	du1_step = 0, dv1_step = 0;
	if (dy1)
		du1_step = du1 / (float)ft_abs(dy1);
	if (dy1)
		dv1_step = dv1 / (float)ft_abs(dy1);
	if (dy1)
	{
		i = y2;
		while (i <= y3)
		{
			int ax = x2 + (float)(i - y2) * dax_step;
			int bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u2 + (float)(i - y2) * du1_step;
			float tex_sv = v2 + (float)(i - y2) * dv1_step;

			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;

			if (ax > bx)
			{
				ft_swap(&ax, &bx);
				ft_swap_f(&tex_su, &tex_eu);
				ft_swap_f(&tex_sv, &tex_ev);
			}

			tex_u = tex_su;
			tex_v = tex_sv;

			float tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;
			j = ax;
			while (j < bx)
			{
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				pxl_put(data, j, i, get_color(tex_u, tex_v, texture), z);
				t += tstep;
				j++;
			}
			i++;
		}
	}
}