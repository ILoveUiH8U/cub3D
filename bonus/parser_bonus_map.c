/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:58:19 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:30:38 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	p_free_int_grid(int **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(grid[i++]);
	free(grid);
}

static int	p_build_door_row(t_game *game, int y)
{
	int	x;

	game->map.door_open[y] = malloc(sizeof(int) * game->map.width);
	if (!game->map.door_open[y])
		return (0);
	x = 0;
	while (x < game->map.width)
	{
		game->map.door_open[y][x] = 0;
		x++;
	}
	return (1);
}

int	p_build_doors(t_game *game)
{
	int	y;

	game->map.door_open = malloc(sizeof(int *) * game->map.height);
	if (!game->map.door_open)
		return (0);
	y = 0;
	while (y < game->map.height)
		game->map.door_open[y++] = NULL;
	y = 0;
	while (y < game->map.height)
	{
		if (!p_build_door_row(game, y))
			return (p_free_int_grid(game->map.door_open, game->map.height), 0);
		y++;
	}
	return (1);
}

static void	p_take_sprite(t_game *game, int x, int y, int *i)
{
	if (game->map.grid[y][x] != 'K')
		return ;
	game->sprites[*i].x = x + 0.5;
	game->sprites[*i].y = y + 0.5;
	game->sprites[*i].dist = 0.0;
	(*i)++;
}

int	p_build_sprites(t_game *game)
{
	int	x;
	int	y;
	int	i;

	if (game->map.sprite_count == 0)
		return (1);
	game->sprites = malloc(sizeof(t_sprite) * game->map.sprite_count);
	if (!game->sprites)
		return (0);
	i = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
			p_take_sprite(game, x++, y, &i);
		y++;
	}
	return (1);
}
