/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:19:49 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:33:13 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	p_is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
			if (game->map.grid[y][x] != '0' && game->map.grid[y][x] != '1'
				&& game->map.grid[y][x] != ' '
				&& !p_is_player(game->map.grid[y][x]))
				return (p_set_error(err, "Invalid character in map"));
			if (p_is_player(game->map.grid[y][x]))
			{
				(*players)++;
				game->map.player_x = x;
				game->map.player_y = y;
				game->map.player_dir = game->map.grid[y][x];
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	p_open(t_game *game, int x, int y)
{
	if (x == 0 || y == 0)
		return (1);
	if (x == game->map.width - 1 || y == game->map.height - 1)
		return (1);
	if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y + 1][x] == ' ')
		return (1);
	if (game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

static int	p_floating_wall(t_game *game, int x, int y)
{
	if (y == 0 || y == game->map.height - 1)
		return (0);
	if (game->map.grid[y][x] != '1')
		return (0);
	if (game->map.grid[y - 1][x] == ' ' && game->map.grid[y + 1][x] == ' ')
		return (1);
	if (x == 0 || x == game->map.width - 1)
		return (0);
	if (game->map.grid[y][x - 1] == ' ' && game->map.grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	p_validate_map(t_game *game, char **err)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	if (!p_scan_map(game, &players, err))
		return (0);
	if (players != 1)
		return (p_set_error(err, "Map must contain exactly one player"));
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (p_floating_wall(game, x, y))
				return (p_set_error(err, "Map is not closed by walls"));
			if (game->map.grid[y][x] != '1' && game->map.grid[y][x] != ' '
				&& p_open(game, x, y))
				return (p_set_error(err, "Map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (1);
}
