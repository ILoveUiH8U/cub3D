/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:19:35 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:08:16 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_in_map(t_game *game, int x, int y)
{
	return (x >= 0 && y >= 0 && x < game->map.width && y < game->map.height);
}

void	use_door(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = (int)(game->view.pos_x + game->view.dir_x * 0.75);
	door_y = (int)(game->view.pos_y + game->view.dir_y * 0.75);
	if (!is_in_map(game, door_x, door_y))
		return ;
	if (game->map.grid[door_y][door_x] == 'D')
		game->map.door_open[door_y][door_x]
			= !game->map.door_open[door_y][door_x];
}
