/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:29:26 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/30 16:41:23 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	game->pos_x = game->map.player_x + 0.5;
	game->pos_y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->povx = 0.66;
		game->povy = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->povx = -0.66;
		game->povy = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->povx = 0;
		game->povy = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->povx = 0;
		game->povy = -0.66;
	}
}
