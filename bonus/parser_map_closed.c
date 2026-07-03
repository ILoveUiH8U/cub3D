/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:10:57 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:31:55 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	p_needs_wall(char c)
{
	return (c != '1' && c != ' ');
}

int	p_closed_map(t_game *game, char **err)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (p_needs_wall(game->map.grid[y][x]) && p_open(game, x, y))
				return (p_set_error(err, "Map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (1);
}

int	p_prepare_bonus_map(t_game *game, char **err)
{
	if (!p_build_doors(game))
		return (p_set_error(err, "Out of memory while building map"));
	if (!p_build_sprites(game))
		return (p_set_error(err, "Out of memory while building map"));
	return (1);
}
