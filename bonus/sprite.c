/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:05:00 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/02 21:02:09 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_img_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	sort_sprites(t_game *game)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < game->map.sprite_count - 1)
	{
		j = 0;
		while (j < game->map.sprite_count - i - 1)
		{
			if (game->sprites[j].dist < game->sprites[j + 1].dist)
			{
				tmp = game->sprites[j];
				game->sprites[j] = game->sprites[j + 1];
				game->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	init_sprite_draw(t_game *game, int i, t_spritedraw *sd)
{
	sd->spx = game->sprites[i].x - game->pos_x;
	sd->spy = game->sprites[i].y - game->pos_y;
	sd->inv = 1.0 / (game->povx * game->dir_y - game->dir_x * game->povy);
	sd->transx = sd->inv * (game->dir_y * sd->spx - game->dir_x * sd->spy);
	sd->transy = sd->inv * (-game->povy * sd->spx + game->povx * sd->spy);
	sd->bob = (int)(sin((game->frame + (i * 20)) * 0.08) * 12.0);
	sd->sph = abs((int)(HEIGHT / sd->transy));
	sd->spw = abs((int)(HEIGHT / sd->transy));
	sd->spx0 = -sd->spw / 2 + (int)((WIDTH / 2) * (1 + sd->transx
				/ sd->transy));
	sd->spx1 = sd->spw / 2 + (int)((WIDTH / 2) * (1 + sd->transx
				/ sd->transy));
	sd->spy0 = -sd->sph / 2 + HEIGHT / 2 + sd->bob;
	sd->spy1 = sd->sph / 2 + HEIGHT / 2 + sd->bob;
}

static void	clamp_sprite_draw(t_spritedraw *sd)
{
	if (sd->spx0 < 0)
		sd->spx0 = 0;
	if (sd->spx1 >= WIDTH)
		sd->spx1 = WIDTH - 1;
	if (sd->spy0 < 0)
		sd->spy0 = 0;
	if (sd->spy1 >= HEIGHT)
		sd->spy1 = HEIGHT - 1;
}

static void	draw_sprite(t_game *game, int i)
{
	t_spritedraw	sd;

	init_sprite_draw(game, i, &sd);
	if (sd.transy <= 0)
		return ;
	clamp_sprite_draw(&sd);
	sd.x = sd.spx0;
	while (sd.x <= sd.spx1)
	{
		sd.tex_x = ((sd.x - sd.spx0) * game->tex.sprite.width) / sd.spw;
		if (sd.transy < game->zbuf[sd.x])
		{
			sd.y = sd.spy0;
			while (sd.y <= sd.spy1)
			{
				sd.tex_y = ((sd.y - sd.spy0) * game->tex.sprite.height) / sd.sph;
				sd.color = get_img_pixel(&game->tex.sprite, sd.tex_x, sd.tex_y);
				if ((sd.color & 0xFF000000) == 0)
					put_pixel(&game->img, sd.x, sd.y, sd.color);
				sd.y++;
			}
		}
		sd.x++;
	}
}

void	render_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.sprite_count)
	{
		game->sprites[i].dist = ((game->pos_x - game->sprites[i].x)
				* (game->pos_x - game->sprites[i].x))
			+ ((game->pos_y - game->sprites[i].y)
				* (game->pos_y - game->sprites[i].y));
		i++;
	}
	sort_sprites(game);
	i = 0;
	while (i < game->map.sprite_count)
	{
		draw_sprite(game, i);
		i++;
	}
}
