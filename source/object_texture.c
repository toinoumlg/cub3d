/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 20:56:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "png_to_img.h"
#include "str.h"
#include "swap.h"
#include <fcntl.h>
#include <stdio.h>


void	add_new_uv(t_list_vector2 **uvs, t_list_vector2 *new_uv)
{
	t_list_vector2	*tmp;

	if (!*uvs)
	{
		*uvs = new_uv;
		return ;
	}
	tmp = *uvs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_uv;
}

void	add_uvs(t_list_vector2 **uvs, char *gnl)
{
	t_list_vector2	*new_uv;

	new_uv = malloc(sizeof(t_list_vector2));
	new_uv->u = ft_atof(gnl);
	new_uv->v = ft_atof(skip_value(gnl, 1));
	new_uv->next = NULL;
	add_new_uv(uvs, new_uv);
}

t_vector2	get_uv(t_list_vector2 *uvs, int i)
{
	t_vector2	new;

	while (i != 0)
	{
		uvs = uvs->next;
		i--;
	}
	new.u = uvs->u;
	new.v = uvs->v;
	return (new);
}

void	add_triangle_with_t(t_list_vector3 *verts, t_list_vector2 *uvs,
		t_triangle **mesh, char *gnl)
{
	int			f[6];
	t_triangle	*new_tri;

	new_tri = malloc(sizeof(t_triangle));
	new_tri->next = NULL;
	f[0] = ft_atoi(gnl) - 1;
	f[1] = ft_atoi(skip_value(gnl, 1)) - 1;
	f[2] = ft_atoi(skip_value(gnl, 2)) - 1;
	f[3] = ft_atoi(skip_value(gnl, 3)) - 1;
	f[4] = ft_atoi(skip_value(gnl, 4)) - 1;
	f[5] = ft_atoi(skip_value(gnl, 5)) - 1;
	new_tri->p[0] = get_vector(verts, f[0]);
	new_tri->t[0] = get_uv(uvs, f[1]);
	new_tri->p[1] = get_vector(verts, f[2]);
	new_tri->t[1] = get_uv(uvs, f[3]);
	new_tri->p[2] = get_vector(verts, f[4]);
	new_tri->t[2] = get_uv(uvs, f[5]);
	add_new_triangle(mesh, new_tri);
}


t_obj	load_obj_with_texture(char *object_name, char *texture_name, void *mlx)
{
	char *gnl;
	t_obj new_obj;
	ft_memset(&new_obj, 0, sizeof(t_obj));
	t_list_vector3 *verts = NULL;
	t_list_vector2 *uvs = NULL;
	int fd = open(object_name, O_RDONLY);
	while (fd > 0)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		if (gnl[0] == 'v')
		{
			if (gnl[1] == ' ')
				add_verts(&verts, gnl + 2);
			else
				add_uvs(&uvs, gnl + 3);
		}
		if (gnl[0] == 'f')
			add_triangle_with_t(verts, uvs, &new_obj.mesh, gnl + 2);
		free(gnl);
	}
	free_verts(verts);
	png_to_img(texture_name, &new_obj.texture, mlx);
	return (new_obj);
}