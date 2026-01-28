# Argument check

First check if program is started with only 2 arguments

```c
void	init_cub3d(t_cub3d *data, int ac, char *file)
{
	int	size;

	ft_memset(data, 0, sizeof(t_cub3d));
	if (ac != 2)
		exit_error("No config file provided", data);
	size = try_open(file);
	init_mlx(data);
	copy_config(size, file, data);
	parse_config(data);
	set_timer(data);
}
```

Then check if the file extension match `.cub` and open the file

```c
int	try_open(char *config)
{
	int	fd;

	if (!config || ft_strncmp(ft_strnstr(config, ".cub", ft_strlen(config)),
			".cub", 5))
		exit_error("No map file or invalid extension", NULL);
	fd = open(config, O_RDONLY);
	if (fd < 0)
		exit_error("Wrong config file name", NULL);
	return (file_size(fd));
}
```

Parse the file completely and return the number of lines

```c
static int	file_size(int fd)
{
	char	*tmp;
	int		line_nbr;

	line_nbr = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (*tmp != '\n')
			line_nbr++;
		free(tmp);
	}
	close(fd);
	return (line_nbr);
}
```
