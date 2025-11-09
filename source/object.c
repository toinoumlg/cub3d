/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:41:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "str.h"
#include "swap.h"
#include <fcntl.h>
#include <stdio.h>

void	add_new_triangle(t_triangle **mesh, t_triangle *new_tri)
{
	t_triangle	*tmp;

	if (!*mesh)
	{
		*mesh = new_tri;
		return ;
	}
	tmp = *mesh;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_tri;
}

char	*skip_value(char *str, int value_to_skip)
{
	int	i;

	i = 0;
	while (value_to_skip)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			value_to_skip--;
			while (str[i] != ' ' && str[i] != '/')
				i++;
		}
		else
			i++;
	}
	i++;
	return (str + i);
}

void	add_new_vect(t_list_vector3 **verts, t_list_vector3 *new_v)
{
	t_list_vector3	*tmp;

	if (!*verts)
	{
		*verts = new_v;
		return ;
	}
	tmp = *verts;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_v;
}

void	add_verts(t_list_vector3 **verts, char *gnl)
{
	t_list_vector3	*new_v;

	new_v = malloc(sizeof(t_list_vector3));
	new_v->x = ft_atof(gnl);
	new_v->y = ft_atof(skip_value(gnl, 1));
	new_v->z = ft_atof(skip_value(gnl, 2));
	new_v->next = NULL;
	add_new_vect(verts, new_v);
}

t_vector3	get_vector(t_list_vector3 *verts, int i)
{
	t_vector3	new;

	while (i != 0)
	{
		verts = verts->next;
		i--;
	}
	new.x = verts->x;
	new.y = verts->y;
	new.z = verts->z;
	return (new);
}

void	add_triangle(t_list_vector3 *verts, t_triangle **mesh, char *gnl)
{
	int			f[3];
	t_triangle	*new_tri;

	new_tri = malloc(sizeof(t_triangle));
	new_tri->next = NULL;
	f[0] = ft_atoi(gnl) - 1;
	f[1] = ft_atoi(skip_value(gnl, 1)) - 1;
	f[2] = ft_atoi(skip_value(gnl, 2)) - 1;
	new_tri->p[0] = get_vector(verts, f[0]);
	new_tri->p[1] = get_vector(verts, f[1]);
	new_tri->p[2] = get_vector(verts, f[2]);
	new_tri->color = create_trgb(0, 255, 0, 0);
	add_new_triangle(mesh, new_tri);
}

void	free_verts(t_list_vector3 *verts)
{
	t_list_vector3	*next;

	while (verts)
	{
		next = verts->next;
		free(verts);
		verts = next;
	}
}

t_obj	load_obj(char *file_name)
{
	char *gnl;
	t_obj new_obj;
	int i = 0;

	ft_memset(&new_obj, 0, sizeof(t_obj));
	t_list_vector3 *verts = NULL;
	int fd = open(file_name, O_RDONLY);
	while (fd > 0)
	{
		i++;
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		if (gnl[0] == 'v')
			add_verts(&verts, gnl + 2);
		if (gnl[0] == 'f')
			add_triangle(verts, &new_obj.mesh, gnl + 2);
		free(gnl);
	}
	free_verts(verts);
	return (new_obj);
}