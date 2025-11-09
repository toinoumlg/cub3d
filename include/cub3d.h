/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:01:37 by amalangu          #+#    #+#             */
/*   Updated: 2025/11/09 21:24:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <sys/time.h>

# ifndef CONFIG
#  define CONFIG

#  define WINDOW_WIDTH 1280.0f
#  define WINDOW_HEIGHT 720.0f
#  define FPS 30.0f
#  define WINDOW_NAME "cub3d"
#  define BLACK 0
#  define FNEAR 0.1f
#  define FFAR 1000.0f
#  define FFOV 90.0f
# endif

typedef struct s_timer
{
	struct timeval			last_frame;
	struct timeval			current_time;
	double					time;
	double					delta_time;
}							t_timer;

typedef struct s_vector3
{
	float					x;
	float					y;
	float					z;
	float					w;
}							t_vector3;

typedef struct s_vector2
{
	float					u;
	float					v;
}							t_vector2;

typedef struct s_color
{
	int						r;
	int						g;
	int						b;
}							t_color;

typedef struct s_list_vector3
{
	float					x;
	float					y;
	float					z;
	struct s_list_vector3	*next;
}							t_list_vector3;

typedef struct s_list_vector2
{
	float					u;
	float					v;
	struct s_list_vector2	*next;
}							t_list_vector2;

/// @brief p = point in space
typedef struct s_triangle
{
	t_vector3				p[3];
	t_vector2				t[3];
	int						color;
	struct s_triangle		*next;
}							t_triangle;

typedef struct s_img
{
	void					*ptr;
	char					*addr;
	int						bpp;
	int						lenght;
	int						w;
	int						h;
	int						end;
}							t_img;

typedef struct s_obj
{
	t_triangle				*mesh;
	t_img					texture;
}							t_obj;

typedef struct s_mat4x4
{
	float					mat[4][4];
}							t_mat4x4;

typedef struct s_cub3d
{
	t_obj					object;
	int						frames;
	void					*mlx;
	void					*window;
	t_mat4x4				proj;
	t_vector3				camera;
	t_vector3				look_dir;
	float					yaw;
	t_img					image;
	t_timer					timer;
	float					**z_buffer;
}							t_cub3d;

t_obj						load_obj(char *file_name);
t_obj						load_obj_with_texture(char *object_name,
								char *texture_name, void *mlx);
void						set_mlx(t_cub3d *data);
void						draw_line(int x0, int y0, int x1, int y1,
								t_cub3d *data, int color, float z);
void						get_current_time(t_cub3d *data);
void						set_timer(t_cub3d *data);
int							create_trgb(unsigned char t, unsigned char r,
								unsigned char g, unsigned char b);
void						pxl_put(t_cub3d *data, int x, int y, int color,
								float z);
void						process_mesh(t_cub3d *data);
t_vector3					set_vector3(float x, float y, float z);
void						ft_swap(int *i, int *j);
void						draw_horizontal_line(int xmin, int xmax, int y,
								t_cub3d *data, int color, float z);
int							triange_clipping_against_plane(t_vector3 plane_p,
								t_vector3 plane_n, t_triangle in_tri,
								t_triangle *out_try1, t_triangle *out_try2);
void						draw_texture(int x1, int y1, float u1, float v1,
								int x2, int y2, float u2, float v2, int x3,
								int y3, float u3, float v3, t_img *texture,
								t_cub3d *data, float z);
int							ft_abs(int nb);
// matrix utils
t_vector3					matrix_multiply_vector(t_mat4x4 m, t_vector3 in);
t_triangle					matrix_multiply_triangle(t_mat4x4 m, t_triangle in);
t_mat4x4					matrix_make_idendity(void);
t_mat4x4					matrix_make_rotation_x(float angle_rad);
t_mat4x4					matrix_make_rotation_y(float angle_rad);
t_mat4x4					matrix_make_rotation_z(float angle_rad);
t_mat4x4					matrix_make_translation(float x, float y, float z);
t_mat4x4					matrix_make_projection(void);
t_mat4x4					matrix_multiply_matrix(t_mat4x4 m1, t_mat4x4 m2);

// vector utils
t_vector3					vector_add(t_vector3 v1, t_vector3 v2);
t_vector3					vector_sub(t_vector3 v1, t_vector3 v2);
t_vector3					vector_mul(t_vector3 v, float mult);
t_vector3					vector_div(t_vector3 v, float div);
float						vector_dot_product(t_vector3 v1, t_vector3 v2);
float						vector_lenght(t_vector3 v);
t_vector3					vector_normalize(t_vector3 v);
t_vector3					vector_cross_product(t_vector3 v1, t_vector3 v2);

void						add_new_vect(t_list_vector3 **verts,
								t_list_vector3 *new_v);
void						add_verts(t_list_vector3 **verts, char *gnl);
char						*skip_value(char *str, int value_to_skip);
t_vector3					get_vector(t_list_vector3 *verts, int i);
void						add_new_triangle(t_triangle **mesh,
								t_triangle *new_tri);
void						free_verts(t_list_vector3 *verts);
// utils
float						ft_atof(const char *str);
t_vector3					set_vector3(float x, float y, float z);

#endif