/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:17:32 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/29 20:17:43 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *g)
{
int	x;
int	y;

y = 0;
while (y < HEIGHT)
{
	x = 0;
	while (x < WIDTH)
	{
		put_pixel(&g->img, x, y, 0x000000);
		x++;
	}
	y++;
}
mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);

}
