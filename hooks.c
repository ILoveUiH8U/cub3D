/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:13:39 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/31 22:06:55 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *g, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || my >= g->map.height || mx >= g->map.width)
		return (1);
	return (g->map.grid[my][mx] == '1');
}

void	move_player(t_game *g, double dx, double dy)
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

static void	set_key(t_game *g, int keycode, int value)
{
	if (keycode == KEY_W)
		g->k_w = value;
	else if (keycode == KEY_A)
		g->k_a = value;
	else if (keycode == KEY_S)
		g->k_s = value;
	else if (keycode == KEY_D)
		g->k_d = value;
	else if (keycode == KEY_LEFT)
		g->k_left = value;
	else if (keycode == KEY_RIGHT)
		g->k_right = value;
}

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	(void)g;
	exit(0);
}

int	key_press(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(g);
	set_key(g, keycode, 1);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	set_key(g, keycode, 0);
	return (0);
}
