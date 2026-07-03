/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:29:26 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:07:09 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_view(t_game *game, double dx, double dy, double px)
{
	game->view.dir_x = dx;
	game->view.dir_y = dy;
	game->view.povx = px;
	if (dx != 0)
		game->view.povy = 0.66 * dx;
	else
		game->view.povy = 0;
}

void	init_player(t_game *game)
{
	game->view.pos_x = game->map.player_x + 0.5;
	game->view.pos_y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
		set_view(game, 0, -1, 0.66);
	else if (game->map.player_dir == 'S')
		set_view(game, 0, 1, -0.66);
	else if (game->map.player_dir == 'E')
		set_view(game, 1, 0, 0);
	else if (game->map.player_dir == 'W')
		set_view(game, -1, 0, 0);
}
