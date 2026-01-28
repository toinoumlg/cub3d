---
icon: map
---

# Map

## Initialization&#x20;

### load\_map()

Parse `**config` to find the first line of the map inside

```c
void	load_map(char **config, t_cub3d *data)
{
	while (*config)
	{
		if (map_line(*config))
			return (copy_map(config, data));
		config++;
	}
	exit_error("No map found in config", data);
}
```

### copy\_map()

Allocate map and copy its content from the `**config`

```c
void	copy_map(char **config, t_cub3d *data)
{
	int	i;

	i = 0;
	get_map_size(config, &data->map_size);
	if (data->map_size.x < 3 || data->map_size.y < 3)
		exit_error("Map is too small", data);
	alloc_map(data);
	while (*config)
	{
		if (**config == '\n')
			break ;
		copy_map_row(*config++, data->map[i++], data);
	}
	check_remaining_lines(config, data);
}
```

### check\_remaining\_lines()

Parse all string remaining in `**config` after creating map to find any non white-space character

```c
void	check_remaining_lines(char **config, t_cub3d *data)
{
	int	i;

	while (*config)
	{
		i = 0;
		while ((*config)[i])
		{
			if ((*config)[i] != '\n' && (*config)[i] != ' '
				&& (*config)[i] != '\t' )
				exit_error("Config files has non white-space character after map", data);
			i++;
		}
		config++;
	}
}
```

## Player&#x20;

### set\_player()

Fill value of `t_player`  \
Set default value for the camera plane `data->plane`\
Set look direction `data->player.dir` default value and rotate according to the value on map\
Set `data->player.pos` offset with 0.5 so player start centered on its square and remove

```c
void	set_player(int **map, t_vector2 map_size, t_double2 *plane,
		t_cub3d *data)
{
	t_vector2	coords;

	data->plane = set_double2(0.0, FOV);
	coords = find_player(map, map_size, data);
	data->player.dir = set_double2(1.0, 0.0);
	set_dir(map[coords.y][coords.x], &data->player.dir, plane);
	data->player.pos = set_double2(coords.x + 0.5, coords.y + 0.5);
	map[coords.y][coords.x] = 0;
}
```

### find\_player()

parse the whole `**map` to find the starting position of the player&#x20;

```c
static t_vector2	find_player(int **map, t_vector2 map_size, t_cub3d *data)
{
	t_vector2	i;
	t_vector2	pos;

	pos = set_vector2(-1, -1);
	i = set_vector2(0, 0);
	while (i.y < map_size.y)
	{
		i.x = 0;
		while (i.x < map_size.x)
		{
			if (map[i.y][i.x] == 'N' || map[i.y][i.x] == 'E'
				|| map[i.y][i.x] == 'S' || map[i.y][i.x] == 'W')
			{
				if (pos.y > 0 || pos.x > 0)
					exit_error("Multiple starting position", data);
				pos = i;
			}
			i.x++;
		}
		i.y++;
	}
	if (pos.x < 0 || pos.y < 0)
		exit_error("No player position on map", data);
	return (pos);
}
```

## Checker

### flood\_fill()

Basic flood\_fill algo if it hit a map border or `**map` value of -1 (correspond to white space) exit&#x20;

```c
void	flood_fill(int x, int y, t_vector2 map_size, t_cub3d *data)
{
	int	**map;

	map = data->map;
	if (x < 0 || x >= map_size.x || y < 0 || y >= map_size.y || map[y][x] == -1)
		exit_error("Map contains hole(s)", data);
	if (map[y][x] != 0)
		return ;
	map[y][x] = 2;
	flood_fill(x + 1, y, map_size, data);
	flood_fill(x - 1, y, map_size, data);
	flood_fill(x, y + 1, map_size, data);
	flood_fill(x, y - 1, map_size, data);
	return ;
}
```
