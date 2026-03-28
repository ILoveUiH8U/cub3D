NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Iminilibx-linux -Ilibft

LIBFT = libft/libft.a

SRC = main.c fakeparser1.c fakeparser2.c
OBJ = $(SRC:.c=.o)

LDFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C minilibx-linux
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re