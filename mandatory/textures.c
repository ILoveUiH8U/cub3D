/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:08:57 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/01 00:06:46 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
		cleanup_and_exit(game, "Failed to load texture");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		cleanup_and_exit(game, "Failed to get texture data");
}

void	load_textures(t_game *game)
{
	load_texture(game, game->cfg.no_path, &game->tex.no);
	load_texture(game, game->cfg.so_path, &game->tex.so);
	load_texture(game, game->cfg.we_path, &game->tex.we);
	load_texture(game, game->cfg.ea_path, &game->tex.ea);
}
