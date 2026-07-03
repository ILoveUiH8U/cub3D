/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:11:14 by mnajem           ###   ########.fr       */
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
	return (g->map.grid[my][mx] == '1');
}

static void	move_player(t_game *g, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = g->view.pos_x + dx;
	ny = g->view.pos_y + dy;
	if (!is_wall(g, nx, g->view.pos_y))
		g->view.pos_x = nx;
	if (!is_wall(g, g->view.pos_x, ny))
		g->view.pos_y = ny;
}

static void	rotate_player(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_povx;

	old_dir_x = g->view.dir_x;
	g->view.dir_x = g->view.dir_x * cos(angle) - g->view.dir_y * sin(angle);
	g->view.dir_y = old_dir_x * sin(angle) + g->view.dir_y * cos(angle);
	old_povx = g->view.povx;
	g->view.povx = g->view.povx * cos(angle) - g->view.povy * sin(angle);
	g->view.povy = old_povx * sin(angle) + g->view.povy * cos(angle);
}

void	update_player(t_game *g)
{
	if (g->keys.w)
		move_player(g, g->view.dir_x * MOVE_SPEED, g->view.dir_y * MOVE_SPEED);
	if (g->keys.s)
		move_player(g, -g->view.dir_x * MOVE_SPEED,
			-g->view.dir_y * MOVE_SPEED);
	if (g->keys.a)
		move_player(g, g->view.dir_y * MOVE_SPEED, -g->view.dir_x * MOVE_SPEED);
	if (g->keys.d)
		move_player(g, -g->view.dir_y * MOVE_SPEED, g->view.dir_x * MOVE_SPEED);
	if (g->keys.left)
		rotate_player(g, -ROT_SPEED);
	if (g->keys.right)
		rotate_player(g, ROT_SPEED);
}
