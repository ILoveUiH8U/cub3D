/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 20:35:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_ray_hit(t_game *game, t_ray *ray)
{
	if (game->map.grid[ray->my][ray->mx] == '1')
		return (1);
	if (game->map.grid[ray->my][ray->mx] == 'D'
		&& !game->map.door_open[ray->my][ray->mx])
		return (1);
	return (0);
}

static void	step_ray(t_ray *ray)
{
	if (ray->v.sdx < ray->v.sdy)
	{
		ray->v.sdx += ray->v.ddx;
		ray->mx += ray->sx;
		ray->side = 0;
	}
	else
	{
		ray->v.sdy += ray->v.ddy;
		ray->my += ray->sy;
		ray->side = 1;
	}
}

void	run_dda(t_game *game, t_ray *ray)
{
	while (!is_ray_hit(game, ray))
		step_ray(ray);
}
