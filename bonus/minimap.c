/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:35:30 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/02 15:14:05 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_img *img, t_minipos pos, int size, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(img, pos.x + i, pos.y + j, color);
			i++;
		}
		j++;
	}
}

static int	get_tile_color(t_minidata *mm, t_minipos map)
{
	char	tile;

	if (map.y < 0 || map.y >= mm->game->map.height
		|| map.x < 0 || map.x >= mm->game->map.width)
		return (-1);
	tile = mm->game->map.grid[map.y][map.x];
	if (tile == '1')
		return (MM_WALL_COLOR);
	if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W')
		return (MM_FLOOR_COLOR);
	return (-1);
}

static void	draw_map_tile(t_minidata *mm, t_minipos map)
{
	int			color;
	t_minipos	screen;

	color = get_tile_color(mm, map);
	if (color == -1)
		return ;
	screen.x = mm->center.x + (int)((map.x - mm->game->pos_x) * MM_TILE);
	screen.y = mm->center.y + (int)((map.y - mm->game->pos_y) * MM_TILE);
	draw_square(&mm->game->img, screen, MM_TILE - 1, color);
}

static void	draw_tiles(t_minidata *mm)
{
	t_minipos	map;

	map.y = (int)mm->game->pos_y - MM_RADIUS;
	while (map.y <= (int)mm->game->pos_y + MM_RADIUS)
	{
		map.x = (int)mm->game->pos_x - MM_RADIUS;
		while (map.x <= (int)mm->game->pos_x + MM_RADIUS)
		{
			draw_map_tile(mm, map);
			map.x++;
		}
		map.y++;
	}
}

static void	draw_player_dir(t_minidata *mm)
{
	t_minipos	end;
	int			steps;
	int			i;

	end.x = mm->center.x + (int)(mm->game->dir_x * MM_TILE * 2.0);
	end.y = mm->center.y + (int)(mm->game->dir_y * MM_TILE * 2.0);
	steps = abs(end.x - mm->center.x);
	if (abs(end.y - mm->center.y) > steps)
		steps = abs(end.y - mm->center.y);
	if (steps < 1)
		steps = 1;
	i = 0;
	while (i <= steps)
	{
		put_pixel(&mm->game->img, mm->center.x + ((end.x - mm->center.x) * i)
			/ steps, mm->center.y + ((end.y - mm->center.y) * i) / steps,
			MM_DIR_COLOR);
		i++;
	}
}

static void	draw_player_dot(t_minidata *mm)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= 9)
				put_pixel(&mm->game->img, mm->center.x + x, mm->center.y + y,
					MM_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minidata	mm;
	t_minipos	pos;

	mm.game = game;
	mm.center.x = MM_MARGIN + MM_BORDER + (MM_SIZE / 2);
	mm.center.y = MM_MARGIN + MM_BORDER + (MM_SIZE / 2);
	pos.x = MM_MARGIN;
	pos.y = MM_MARGIN;
	draw_square(&game->img, pos, MM_SIZE + (MM_BORDER * 2), MM_FRAME_COLOR);
	pos.x = MM_MARGIN + MM_BORDER;
	pos.y = MM_MARGIN + MM_BORDER;
	draw_square(&game->img, pos, MM_SIZE, MM_BG_COLOR);
	draw_tiles(&mm);
	draw_player_dir(&mm);
	draw_player_dot(&mm);
}
