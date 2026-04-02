/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:15:31 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/02 19:15:27 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		cleanup_and_exit(g, "mlx_init failed");
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (!g->win)
		cleanup_and_exit(g, "mlx_new_window failed");
	mlx_hook(g->win, EV_KEY_PRESS, MASK_KEY_PRESS, key_press, g);
	mlx_hook(g->win, EV_KEY_RELEASE, MASK_KEY_RELEASE, key_release, g);
	mlx_hook(g->win, EV_DESTROY, 0, close_window, g);
	init_mouse(g);
}
