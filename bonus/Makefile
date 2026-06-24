NAME = ../cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I.. -I../minilibx-linux -I../libft

LIBFT = ../libft/libft.a
MLX = ../minilibx-linux/libmlx.a

SRC = main.c parser_core.c parser_read.c parser_color.c \
	parser_config.c parser_map_grid.c parser_map_check.c parser_bonus_map.c \
	parser_map_closed.c parser_free.c errors.c utils.c \
	raycasting.c ray_step.c ray_draw.c hooks.c player_move.c mlx_init.c \
	draw.c render.c player_init.c textures.c minimap.c \
	minimap_player.c image_utils.c door.c mouse.c sprite.c sprite_sort.c
OBJ = $(SRC:.c=.o)

LDFLAGS = -L../minilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ../libft

$(MLX):
	$(MAKE) -C ../minilibx-linux

$(NAME): FORCE $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

FORCE:

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE
