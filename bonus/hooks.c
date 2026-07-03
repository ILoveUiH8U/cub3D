/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:13:39 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:07:59 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_game *g, int keycode, int value)
{
	if (keycode == KEY_W)
		g->keys.w = value;
	else if (keycode == KEY_A)
		g->keys.a = value;
	else if (keycode == KEY_S)
		g->keys.s = value;
	else if (keycode == KEY_D)
		g->keys.d = value;
	else if (keycode == KEY_LEFT)
		g->keys.left = value;
	else if (keycode == KEY_RIGHT)
		g->keys.right = value;
}

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(g);
	if (keycode == KEY_E)
		use_door(g);
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
