NAME = ../cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I.. -I../minilibx-linux -I../libft

LIBFT = ../libft/libft.a
MLX = ../minilibx-linux/libmlx.a

SRC = main.c parser_core.c parser_read.c parser_color.c \
	parser_config.c parser_map_grid.c parser_map_check.c errors.c utils.c \
	parser_free.c raycasting.c hooks.c mlx_init.c draw.c render.c \
	player_init.c textures.c
OBJ = $(SRC:.c=.o)

LDFLAGS = -L../minilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ../libft

$(MLX):
	$(MAKE) -C ../minilibx-linux

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
