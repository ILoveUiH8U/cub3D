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

void	run_dda(t_game *game, t_ray *ray)
{
	while (game->map.grid[ray->my][ray->mx] != '1')
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
}
