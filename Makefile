NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -std=gnu89

OBJECTS_DIR = build
INCLUDE_DIR = include
MLX_DIR = mlx
LIBFT_DIR = libft

SOURCE_DIR = source
SOURCES_MAIN = main utils init object object_texture draw timer \
	process_mesh vector_utils matrix_utils png_to_img clipping draw_texture

SOURCES = $(addprefix $(SOURCE_DIR)/, $(addsuffix .c, $(SOURCES_MAIN))) 
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(OBJECTS_DIR)/%.o)
INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lpng -lm $(LIBFT_LIB)
DEP = $(OBJECTS:.o=.d)

all: $(MLX_LIB) $(LIBFT_LIB) $(OBJECTS_DIR) $(NAME)

norminette:
	clear
	norminette $(SOURCE_DIR) $(INCLUDE_DIR)

$(NAME): $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJECTS) $(LIBS) 

$(MLX_LIB):
	make -C $(MLX_DIR) $(FLUSH_BOTH)

$(LIBFT_LIB): $(SOURCES_LIBFT)
	make -C $(LIBFT_DIR) $(FLUSH_STDOUT)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -g -c -o $@ $<

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf $(OBJECTS_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re norminette libft

-include $(DEP)