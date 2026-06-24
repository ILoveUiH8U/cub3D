/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 00:00:00 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 00:00:00 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WIDTH 1280
# define HEIGHT 720
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
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.025

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
}	t_tex;

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

typedef struct s_game
{
	t_cfg	cfg;
	t_map	map;
	int		k_w;
	int		k_a;
	int		k_s;
	int		k_d;
	int		k_left;
	int		k_right;
	double	pos_x;
	double	pos_y;
	void	*mlx;
	void	*win;
	double	dir_x;
	double	dir_y;
	double	povx;
	double	povy;
	t_tex	tex;
	t_img	img;
}	t_game;

void	error_exit(char *msg);
void	cleanup_and_exit(t_game *game, char *msg);
void	free_map(char **map);
int		get_width(char *row);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_window(void *param);
void	init_mlx(t_game *g);
void	load_textures(t_game *game);
int		render_frame(void *param);
void	cast_rays(t_game *game);
void	update_player(t_game *g);
void	rotate_player(t_game *g, double angle);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_game *g, t_ray *ray, int start, int end);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda(t_game *game, t_ray *ray);
void	run_dda(t_game *game, t_ray *ray);
int		parse_cub_file(const char *path, t_game *game);
void	init_game(t_game *game);
void	free_game(t_game *game);
void	init_player(t_game *game);
int		p_is_blank(char *line);
int		p_set_error(char **err, char *msg);
int		p_has_cub(char *path);
void	p_free_lines(char **lines, int count);
int		p_read_file(char *path, t_scene *scene);
int		p_readable_file(char *path);
int		p_read_config(t_game *game, t_scene *scene);
int		p_build_map(t_game *game, t_scene *scene);
int		p_validate_map(t_game *game, char **err);
int		p_save_texture(char **dst, char *value, char **err);
int		p_save_rgb(char *value, int *dst, int *flag, char **err);
void	p_skip_space(char *line, int *i);

#endif
