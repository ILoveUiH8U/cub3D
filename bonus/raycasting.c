/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:00:06 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/02 21:02:37 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->x = x;
	ray->v.cam = 2.0 * x / (double)WIDTH - 1.0;
	ray->v.dir_x = game->dir_x + game->povx * ray->v.cam;
	ray->v.dir_y = game->dir_y + game->povy * ray->v.cam;
}

static double	unit_step(double dir)
{
	if (dir == 0.0)
		return (1e30);
	return (fabs(1.0 / dir));
}

static void	load_x_axis(t_game *game, t_ray *ray)
{
	if (ray->v.dir_x < 0.0)
	{
		ray->sx = -1;
		ray->v.sdx = (game->pos_x - ray->mx) * ray->v.ddx;
	}
	else
	{
		ray->sx = 1;
		ray->v.sdx = (ray->mx + 1.0 - game->pos_x) * ray->v.ddx;
	}
}

static void	load_y_axis(t_game *game, t_ray *ray)
{
	if (ray->v.dir_y < 0.0)
	{
		ray->sy = -1;
		ray->v.sdy = (game->pos_y - ray->my) * ray->v.ddy;
	}
	else
	{
		ray->sy = 1;
		ray->v.sdy = (ray->my + 1.0 - game->pos_y) * ray->v.ddy;
	}
}

void	init_dda(t_game *game, t_ray *ray)
{
	ray->mx = (int)game->pos_x;
	ray->my = (int)game->pos_y;
	ray->v.ddx = unit_step(ray->v.dir_x);
	ray->v.ddy = unit_step(ray->v.dir_y);
	load_x_axis(game, ray);
	load_y_axis(game, ray);
}
