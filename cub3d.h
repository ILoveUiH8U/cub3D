#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <mlx.h>
# include "libft/libft.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FLOOR_COLOR 0x2E2E2E
# define CEIL_COLOR 0x4A6274
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_M 109
# define KEY_SPACE 32
# define EV_KEY_PRESS 2
# define EV_KEY_RELEASE 3
# define EV_DESTROY 17
# define MASK_KEY_PRESS 1L
# define MASK_KEY_RELEASE 2L
# define MASK_DESTROY 0L

typedef struct s_cfg
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
	int		has_floor;
	int		has_ceil;
}t_cfg;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	char	player_dir;
}t_map;

typedef struct s_game
{
	t_cfg	cfg;
	t_map	map;
}t_game;

typedef struct s_img
{
void *img;
char *addr;
int bpp;
int line_len;
int endian;
} t_img;

typedef struct s_game
{
void *mlx;
void *win;
t_img img;
} t_game;

/* errors */
void error_exit(char *msg);

/* utils */
void free_map(char **map);
int get_width(char *row);

/* hooks */
int key_press(int keycode, void *param);
int close_window(void *param);

/* mlx */
void init_mlx(t_game *g);

/* render */
void render_frame(t_game *g);

/* draw */
void put_pixel(t_img *img, int x, int y, int color);
void draw_vertical_line(t_game *g, int x, int start, int end, int color);

#endif
int		parse_cub_file(const char *path, t_game *game);
void	init_game(t_game *game);
void	free_game(t_game *game);
int		build_and_validate_map(t_game *game, char **lines, int start, int count,
			char **err_msg);

#endif
