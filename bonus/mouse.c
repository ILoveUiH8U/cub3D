/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:19:35 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 19:48:07 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	center_mouse(t_game *game)
{
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
}

void	init_mouse(t_game *g)
{
	mlx_hook(g->win, EV_MOUSE_MOVE, MASK_MOUSE_MOVE, mouse_move_hook, g);
	mlx_mouse_hide(g->mlx, g->win);
	center_mouse(g);
}

int	mouse_move_hook(int x, int y, void *param)
{
	t_game	*g;
	int		delta_x;

	g = (t_game *)param;
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	delta_x = x - (WIDTH / 2);
	if (delta_x != 0)
		rotate_view(g, delta_x * MOUSE_SENSITIVITY);
	center_mouse(g);
	return (0);
}
