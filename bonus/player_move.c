/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 20:35:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *g, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || my >= g->map.height || mx >= g->map.width)
		return (1);
	if (g->map.grid[my][mx] == 'D' && !g->map.door_open[my][mx])
		return (1);
	return (g->map.grid[my][mx] == '1');
}

static void	move_player(t_game *g, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = g->pos_x + dx;
	ny = g->pos_y + dy;
	if (!is_wall(g, nx, g->pos_y))
		g->pos_x = nx;
	if (!is_wall(g, g->pos_x, ny))
		g->pos_y = ny;
}

void	rotate_view(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_povx;

	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
	g->dir_y = old_dir_x * sin(angle) + g->dir_y * cos(angle);
	old_povx = g->povx;
	g->povx = g->povx * cos(angle) - g->povy * sin(angle);
	g->povy = old_povx * sin(angle) + g->povy * cos(angle);
}

void	update_player(t_game *g)
{
	if (g->k_w)
		move_player(g, g->dir_x * MOVE_SPEED, g->dir_y * MOVE_SPEED);
	if (g->k_s)
		move_player(g, -g->dir_x * MOVE_SPEED, -g->dir_y * MOVE_SPEED);
	if (g->k_a)
		move_player(g, g->dir_y * MOVE_SPEED, -g->dir_x * MOVE_SPEED);
	if (g->k_d)
		move_player(g, -g->dir_y * MOVE_SPEED, g->dir_x * MOVE_SPEED);
	if (g->k_left)
		rotate_view(g, -ROT_SPEED);
	if (g->k_right)
		rotate_view(g, ROT_SPEED);
}
