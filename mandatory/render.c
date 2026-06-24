/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:17:32 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/01 17:53:10 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_rows(t_game *game, int y, int end, int color)
{
	char	*row;
	int		x;
	int		step;

	step = game->img.bpp / 8;
	while (y < end)
	{
		row = game->img.addr + (y * game->img.line_len);
		x = 0;
		while (x < WIDTH)
		{
			*(unsigned int *)(row + (x * step)) = color;
			x++;
		}
		y++;
	}
}

int	render_frame(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	update_player(g);
	fill_rows(g, 0, HEIGHT / 2, g->cfg.ceil_color);
	fill_rows(g, HEIGHT / 2, HEIGHT, g->cfg.floor_color);
	cast_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}
