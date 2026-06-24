/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:09:42 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:33:31 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	p_free_paths(t_game *game)
{
	free(game->cfg.no_path);
	free(game->cfg.so_path);
	free(game->cfg.we_path);
	free(game->cfg.ea_path);
	game->cfg.no_path = NULL;
	game->cfg.so_path = NULL;
	game->cfg.we_path = NULL;
	game->cfg.ea_path = NULL;
}

static void	p_free_map_data(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.grid && i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
	if (game->map.door_open)
		p_free_int_grid(game->map.door_open, game->map.height);
	game->map.grid = NULL;
	game->map.door_open = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = 0;
}

static void	p_destroy_img(void *mlx, t_img *img)
{
	if (mlx && img->img)
		mlx_destroy_image(mlx, img->img);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

static void	p_free_mlx(t_game *game)
{
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->mlx = NULL;
}

void	free_game(t_game *game)
{
	p_free_paths(game);
	p_free_map_data(game);
	free(game->sprites);
	game->sprites = NULL;
	game->map.sprite_count = 0;
	p_destroy_img(game->mlx, &game->tex.no);
	p_destroy_img(game->mlx, &game->tex.so);
	p_destroy_img(game->mlx, &game->tex.we);
	p_destroy_img(game->mlx, &game->tex.ea);
	p_destroy_img(game->mlx, &game->tex.door);
	p_destroy_img(game->mlx, &game->tex.sprite);
	p_destroy_img(game->mlx, &game->img);
	p_free_mlx(game);
}
