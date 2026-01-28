---
description: All functions used multiple times around the project
icon: wrench
---

# Utils

## Parsing

### `find_in_config()`

Parse the `config` array and return string starting with `to_find`  \
Return `NULL` if not found

{% code title="source/config/utils.c" %}
```c
char	*find_in_config(char *to_find, char **config)
{
	while (*config)
	{
		if (!ft_strncmp(to_find, *config, ft_strlen(to_find)))
			return (*config);
		config++;
	}
	return (NULL);
}
```
{% endcode %}

### ft\_strlen\_with\_tab`()`

For map row, increase by 4 for `'\t'`  to reflect how map is in config file

{% code title="source/config/utils.c" %}
```c
int	ft_strlen_with_tab(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\t')
			size += 4;
		else
			size++;
		i++;
	}
	return (size);
}

```
{% endcode %}

### map\_line`()`

Parse `line`, return 0 if `line` contains an other character than what is expected in the map\
Else return 1

{% code title="source/config/map.c" %}
```c
int map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}
```
{% endcode %}

## Allocation

### alloc\_config`()`

Allocate `**config`  of `size` &#x20;

{% code title="source/config/alloc.c" %}
```c
void	allocate_config(int size, t_cub3d *data)
{
	data->config = malloc(sizeof(char *) * (size + 1));
	if (!data->config)
		exit_error("Memory allocation failed.", NULL);
	ft_memset(data->config, 0, sizeof(char *) * (size + 1));
}
```
{% endcode %}

### alloc\_map`()`

Allocate `**map` and set every value to `-1` &#x20;

{% code title="source/config/alloc.c" %}
```c
void	alloc_map(t_cub3d *data)
{
	int	i;

	data->map = malloc(sizeof(int *) * data->map_size.y);
	if (!data->map)
		exit_error("Allocation failed during alloc_map", data);
	i = 0;
	while (i < data->map_size.y)
	{
		data->map[i] = malloc(sizeof(int) * data->map_size.x);
		if (!data->map[i])
		{
			data->map_size.y = i;
			exit_error("Allocation failed during alloc_map", data);
		}
		ft_memset(data->map[i++], -1, sizeof(int) * data->map_size.x);
	}
}
```
{% endcode %}

## Math

### `ft_abs()`

Return the absolute value of `nb`

{% code title="source/utils/utils.c" %}
```c
double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
```
{% endcode %}

### `set_double2()`

Return a `t_double2`  containing `x` and `y` given floats

{% code title="source/utils/utils.c" %}
```c
t_double2	set_double2(float x, float y)
{
	t_double2	new_double2;

	new_double2.x = x;
	new_double2.y = y;
	return (new_double2);
}
```
{% endcode %}

### `set_vector2()`

Return a `t_vector2` containing `x` and `y` given integers

{% code title="source/utils/utils.c" %}
```c
t_vectsource/graphic/utils.cor2	set_vector2(int x, int y)
{
	t_vector2	new_vector2;

	new_vector2.x = x;
	new_vector2.y = y;
	return (new_vector2);
}
```
{% endcode %}

## MinilibX

### `create_trgb()`

Return a created color from the given `unsigned char t,r,g,b`  \
Corresponding to transparency, red, green and blue respectively&#x20;

{% code title="source/graphic/utils.c" %}
```c
int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
```
{% endcode %}

## MinilibX

### `create_trgb()`

Return a created color from the given `unsigned char t,r,g,b`  \
Corresponding to transparency, red, green and blue respectively&#x20;

{% code title="source/graphic/utils.c" %}
```c
int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
```
{% endcode %}

### `pxl_put()`

Change the color of pixel at the position `x` and `y`  to a given `img` \
The address of this specific pixel is pointed by `*pxl` with the use of `addr_offset()` \
After that we change the value under `*pxl` with `color`

{% code title="source/graphic/utils.c" %}
```c
static int	addr_offset(t_img img, int x, int y)
{
	return (y * img.lenght + x * (img.bpp / 8));
}

void	pxl_put(t_img img, int x, int y, int color)
{
	char	*pxl;

	pxl = img.addr + addr_offset(img, x, y);
	*(unsigned int *)pxl = color;
}
```
{% endcode %}

### `get_texture_pixel_color()`

Same as `pxl_put()`  but return the value under `*pxl`

{% code title="source/graphic/utils.c" %}
```c
int	get_texture_pixel_color(t_img texture, int text_x, int text_y)
{
	char	*pxl;

	pxl = texture.addr + addr_offset(texture, text_x, text_y);
	return (*(unsigned int *)pxl);
}
```
{% endcode %}

## Free

### `free_cub3d()`

Free the whole `t_cub3d` structure

{% code title="source/utils/free.c" %}
```c
int	free_cub3d(t_cub3d *data)
{
	free_mlx(data);
	free_map(data->map, data->map_size.y);
	free_config(data->config);
	ft_close(&data->fd);
	return (1);
}
```
{% endcode %}

### `free_mlx()`

For every MinilibX related, destroy and free if initialized&#x20;

{% code title="source/utils/free.c" %}
```c
static void	free_mlx(t_cub3d *data)
{
	if (data->buffer.ptr)
		mlx_destroy_image(data->mlx, data->buffer.ptr);
	if (data->textures[0].ptr)
		mlx_destroy_image(data->mlx, data->textures[0].ptr);
	if (data->textures[1].ptr)
		mlx_destroy_image(data->mlx, data->textures[1].ptr);
	if (data->textures[2].ptr)
		mlx_destroy_image(data->mlx, data->textures[2].ptr);
	if (data->textures[3].ptr)
		mlx_destroy_image(data->mlx, data->textures[3].ptr);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
```
{% endcode %}

### `free_map()`

If allocated, free `**map` with `y` as a limit

{% code title="source/utils/free.c" %}
```c
static void	free_map(int **map, int y)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < y)
		free(map[i++]);
	free(map);
}
```
{% endcode %}

### free\_config`()`

If allocated, free `**array`

{% code title="source/utils/free.c" %}
```c
void	free_config(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
```
{% endcode %}

### `ft_close()`

{% code title="source/utils/free.c" %}
```c
static void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}
```
{% endcode %}
