# t\_cub3d

```c
typedef struct s_cub3d
{
	int				fd;
	void			*mlx; // pointer to function void *mlx_init()  
	int				**map; // array of the map
	char			**config; // array of the duplicated configuration file
	t_vector2		map_size; // map limit size
	void			*window; // pointer to the funtion void *mlx_new_window()
	int				floor; // floor color
	int				ceiling; // ceiling color
	t_img			textures[4]; // wall textures
	t_img			buffer; // buffer image
	t_timer			timer; // timer
	t_double2		plane; // camera plane
	t_player		player; // player struct
}					t_cub3d;

```
