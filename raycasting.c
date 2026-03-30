/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:00:06 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/30 20:43:14 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, int x, double *ray_x, double *ray_y)
{
	double	cam;

	cam = 2.0 * x / (double)WIDTH - 1.0;
	*ray_x = game->dir_x + game->povx * cam;
	*ray_y = game->dir_y + game->povy * cam;
}

static void	cast_a_ray(t_game *game, int x)
{
	double	ray_x;
	double	ray_y;

	init_ray(game, x, &ray_x, &ray_y);
	(void)ray_x;
	(void)ray_y;
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_a_ray(game, x);
		x++;
	}
}
