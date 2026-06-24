/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:19:49 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:31:37 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	p_is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	p_allowed(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'D' || c == 'K' || p_is_player(c))
		return (1);
	return (0);
}

static int	p_scan_cell(t_game *game, int x, int y, int *players)
{
	if (p_is_player(game->map.grid[y][x]))
	{
		(*players)++;
		game->map.player_x = x;
		game->map.player_y = y;
		game->map.player_dir = game->map.grid[y][x];
	}
	if (game->map.grid[y][x] == 'K')
		game->map.sprite_count++;
	return (1);
}

static int	p_scan_map(t_game *game, int *players, char **err)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!p_allowed(game->map.grid[y][x]))
				return (p_set_error(err, "Invalid character in map"));
			p_scan_cell(game, x, y, players);
			x++;
		}
		y++;
	}
	return (1);
}

int	p_validate_map(t_game *game, char **err)
{
	int	players;

	players = 0;
	game->map.sprite_count = 0;
	if (!p_scan_map(game, &players, err))
		return (0);
	if (players != 1)
		return (p_set_error(err, "Map must contain exactly one player"));
	if (!p_prepare_bonus_map(game, err))
		return (0);
	return (p_closed_map(game, err));
}
