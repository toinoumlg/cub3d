---
icon: window-maximize
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
    - https://app.gitbook.com/s/yE16Xb3IemPxJWydtPOj/basics/editor
---

# MinilibX Initialization

Initialize mlx, open a new window and create the buffer image everything stored in data structure

```c
void	init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Failed to initialize minilibx", data);
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (!data->window)
		exit_error("Failed to open new window", data);
	data->buffer.ptr = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->buffer.ptr)
		exit_error("Initializing buffer image", data);
	data->buffer.addr = mlx_get_data_addr(data->buffer.ptr, &data->buffer.bpp,
			&data->buffer.lenght, &data->buffer.end);
	if (!data->buffer.addr)
		exit_error("Getting buffer image address", data);
}
```

