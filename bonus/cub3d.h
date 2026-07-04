/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 00:00:00 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 18:16:00 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include "libft/libft.h"

# define WIDTH 1280
# define HEIGHT 720
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_E 101
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define EV_KEY_PRESS 2
# define EV_KEY_RELEASE 3
# define EV_MOUSE_MOVE 6
# define EV_DESTROY 17
# define MASK_KEY_PRESS 1L
# define MASK_KEY_RELEASE 2L
# define MASK_MOUSE_MOVE 64
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.01
# define MOUSE_SENSITIVITY 0.002
# define MM_MARGIN 20
# define MM_BORDER 2
# define MM_TILE 14
# define MM_RADIUS 5
# define MM_SIZE 154
# define MM_FRAME_COLOR 0x101722
# define MM_BG_COLOR 0x1C2530
# define MM_WALL_COLOR 0xD9D9D9
# define MM_FLOOR_COLOR 0x800080
# define MM_PLAYER_COLOR 0xD94F4F
# define MM_DIR_COLOR 0xF3D36B

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
}	t_cfg;

typedef struct s_map
{
	char	**grid;
	int		**door_open;
	int		sprite_count;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_scene
{
	char	**lines;
	int		count;
	int		start;
	char	**err;
}	t_scene;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_tex
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	door;
	t_img	sprite;
}	t_tex;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
}	t_sprite;

typedef struct s_rval
{
	double	cam;
	double	dir_x;
	double	dir_y;
	double	ddx;
	double	ddy;
	double	sdx;
	double	sdy;
	double	dist;
}	t_rval;

typedef struct s_ray
{
	int		x;
	int		mx;
	int		my;
	int		sx;
	int		sy;
	int		side;
	t_img	*tex;
	t_rval	v;
}	t_ray;

typedef struct s_column
{
	int	start;
	int	end;
	int	tex_x;
}	t_column;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_view
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	povx;
	double	povy;
}	t_view;

typedef struct s_game
{
	t_cfg		cfg;
	t_map		map;
	t_keys		keys;
	t_view		view;
	void		*mlx;
	void		*win;
	int			frame;
	double		zbuf[WIDTH];
	t_sprite	*sprites;
	t_tex		tex;
	t_img		img;
}	t_game;

typedef struct s_sprite_proj
{
	double	spx;
	double	spy;
	double	inv;
	double	transx;
	double	transy;
}	t_sprite_proj;

typedef struct s_sprite_box
{
	int		bob;
	int		sph;
	int		spw;
	int		spx0;
	int		spx1;
	int		spy0;
	int		spy1;
}	t_sprite_box;

typedef struct s_spritedraw
{
	t_sprite_proj	proj;
	t_sprite_box	box;
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
}	t_spritedraw;

typedef struct s_minipos
{
	int	x;
	int	y;
}	t_minipos;

typedef struct s_minidata
{
	t_game		*game;
	t_minipos	center;
}	t_minidata;

void	cleanup_and_exit(t_game *game, char *msg);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_window(void *param);
void	init_mlx(t_game *g);
void	init_mouse(t_game *g);
void	load_textures(t_game *game);
int		render_frame(void *param);
void	cast_rays(t_game *game);
void	render_sprites(t_game *game);
void	update_player(t_game *g);
void	paint_minimap_frame(t_game *game, t_minidata *mm);
void	draw_minimap_tiles(t_minidata *mm);
void	draw_minimap_player(t_minidata *mm);
void	draw_square(t_img *img, t_minipos pos, int size, int color);
void	draw_texture_square(t_img *img, t_img *tex, t_minipos pos, int size);
int		get_img_pixel(t_img *img, int x, int y);
void	rotate_view(t_game *g, double angle);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda(t_game *game, t_ray *ray);
void	run_dda(t_game *game, t_ray *ray);
void	sort_sprites(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_game *g, t_ray *ray, int start, int end);
void	use_door(t_game *game);
void	draw_minimap(t_game *game);
int		parse_cub_file(const char *path, t_game *game);
void	init_game(t_game *game);
void	free_game(t_game *game);
void	init_player(t_game *game);
int		p_is_blank(char *line);
int		p_set_error(char **err, char *msg);
void	p_free_lines(char **lines, int count);
int		p_read_file(char *path, t_scene *scene);
int		p_readable_file(char *path);
int		p_read_config(t_game *game, t_scene *scene);
int		p_build_map(t_game *game, t_scene *scene);
int		p_validate_map(t_game *game, char **err);
int		p_prepare_bonus_map(t_game *game, char **err);
int		p_closed_map(t_game *game, char **err);
int		p_build_doors(t_game *game);
int		p_build_sprites(t_game *game);
int		p_save_texture(char **dst, char *value, char **err);
int		p_save_rgb(char *value, int *dst, int *flag, char **err);
void	p_skip_space(char *line, int *i);
void	p_free_int_grid(int **grid, int rows);
int		abs_int(int value);

#endif
