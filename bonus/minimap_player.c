/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 20:35:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_dir(t_minidata *mm)
{
	t_minipos	end;
	int			steps;
	int			dx;
	int			dy;
	int			i;

	end.x = mm->center.x + (int)(mm->game->dir_x * MM_TILE * 2.0);
	end.y = mm->center.y + (int)(mm->game->dir_y * MM_TILE * 2.0);
	dx = abs_int(end.x - mm->center.x);
	dy = abs_int(end.y - mm->center.y);
	steps = dx;
	if (dy > steps)
		steps = dy;
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

void	draw_minimap_player(t_minidata *mm)
{
	draw_player_dir(mm);
	draw_player_dot(mm);
}

void	paint_minimap_frame(t_game *game, t_minidata *mm)
{
	t_minipos	pos;

	pos.x = MM_MARGIN;
	pos.y = MM_MARGIN;
	draw_square(&game->img, pos, MM_SIZE + (MM_BORDER * 2), MM_FRAME_COLOR);
	pos.x = MM_MARGIN + MM_BORDER;
	pos.y = MM_MARGIN + MM_BORDER;
	draw_square(&game->img, pos, MM_SIZE, MM_BG_COLOR);
	(void)mm;
}

void	draw_minimap(t_game *game)
{
	t_minidata	mm;

	mm.game = game;
	mm.center.x = MM_MARGIN + MM_BORDER + (MM_SIZE / 2);
	mm.center.y = MM_MARGIN + MM_BORDER + (MM_SIZE / 2);
	paint_minimap_frame(game, &mm);
	draw_minimap_tiles(&mm);
	draw_minimap_player(&mm);
}
