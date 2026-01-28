---
icon: sign-posts-wrench
---

# Installation & Build

### Clone cub3d repository

```bash
git clone git@github.com:toinoumlg/cub3d.git
cd cub3d
```

### Clone MinilibX repository

```bash
git clone https://github.com/42paris/minilibx-linux.git
```

### Build using Make

Since this project use the MinilibX we need to include it when compiling.

```make
MLX_DIR = ./minilibx-linux ## what ever you choose to clone mlx into
INCLUDES = -I/usr/include -I./$(MLX_DIR) -I./libft/include -I./include

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c -o $@ $<
```

We also need to import the libraries when linking our objects.&#x20;

```make
LIBS = -L$(MLX_DIR) -l$(MLX_DIR) -L/usr/lib/X11 -lXext -lX11 -lm

$(NAME): $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJECTS) $(LIBS)
```

At the root of the project we can now compile using Make

```bash
make
```

