/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 20:35:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_sprite(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_sprites(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.sprite_count - 1)
	{
		j = 0;
		while (j < game->map.sprite_count - i - 1)
		{
			if (game->sprites[j].dist < game->sprites[j + 1].dist)
				swap_sprite(&game->sprites[j], &game->sprites[j + 1]);
			j++;
		}
		i++;
	}
}
