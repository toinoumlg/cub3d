---
icon: gears
layout:
  width: default
  title:
    visible: true
  description:
    visible: true
  tableOfContents:
    visible: true
  outline:
    visible: true
  pagination:
    visible: true
  metadata:
    visible: true
metaLinks:
  alternates:
    - https://app.gitbook.com/s/yE16Xb3IemPxJWydtPOj/basics/markdown
---

# Config file

First copy the whole file to an array of strings for easier manipulation easier later in parsing \
Also trim the '\n' at the end of a line if not empty

```c
void	copy_config(int size, char *file, t_cub3d *data)
{
	int		i;
	char	*tmp;

	i = 0;
	allocate_config(size, data);
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		exit_error("Failed to open config file", data);
	while (i < size)
	{
		tmp = get_next_line(data->fd);
		if (!tmp)
			exit_error("Allocation failed during config copy", data);
		if (*tmp == '\n')
		{
			data->config[i++] = tmp;
			continue ;
		}
		data->config[i] = ft_strtrim(tmp, "\n");
		free(tmp);
		if (!data->config[i++])
			exit_error("Allocation failed during trim of config", data);
	}
}
```

Fill the cub3d structure will all data

```c
void	parse_config(t_cub3d *data)
{
	data->ceiling = set_color_from_config("C ", data->config, data);
	data->floor = set_color_from_config("F ", data->config, data);
	data->textures[0] = init_texture_from_config("SO ", data);
	data->textures[1] = init_texture_from_config("WE ", data);
	data->textures[2] = init_texture_from_config("NO ", data);
	data->textures[3] = init_texture_from_config("EA ", data);
	load_map(data->config, data);
	set_player(data->map, data->map_size, &data->plane, data);
	flood_fill(data->player.pos.x, data->player.pos.y, data->map_size, data);
	restore_map(data->map, data->map_size);
}

```

