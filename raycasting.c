/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:00:06 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/30 19:43:09 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_a_ray(t_game *game, int x)
{
	(void)game;
	(void)x;
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
