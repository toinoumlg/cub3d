---
description: When everything goes wrong
icon: binary-slash
---

# Error Handling

Write onto the terminal `*error`, free `t_cub3d`  and exit with error status

```c
void	exit_error(char *error, t_cub3d *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	if (data)
		free_cub3d(data);
	exit(1);
}
```

```
Error\n
No player position on map\n
```
