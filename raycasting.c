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

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->x = x;
	ray->v.cam = 2.0 * x / (double)WIDTH - 1.0;
	ray->v.dir_x = game->dir_x + game->povx * ray->v.cam;
	ray->v.dir_y = game->dir_y + game->povy * ray->v.cam;
}

static void	init_dda(t_game *game, t_ray *ray)
{
	ray->mx = (int)game->pos_x;
	ray->my = (int)game->pos_y;
	if (ray->v.dir_x == 0)
		ray->v.ddx = 1e30;
	else
		ray->v.ddx = fabs(1.0 / ray->v.dir_x);
	if (ray->v.dir_y == 0)
		ray->v.ddy = 1e30;
	else
		ray->v.ddy = fabs(1.0 / ray->v.dir_y);
}

static void	cast_a_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, &ray, x);
	init_dda(game, &ray);
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
