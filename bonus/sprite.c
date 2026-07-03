/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:05:00 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:06:30 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_draw(t_game *game, int i, t_spritedraw *sd)
{
	sd->proj.spx = game->sprites[i].x - game->view.pos_x;
	sd->proj.spy = game->sprites[i].y - game->view.pos_y;
	sd->proj.inv = 1.0 / (game->view.povx * game->view.dir_y
			- game->view.dir_x * game->view.povy);
	sd->proj.transx = sd->proj.inv * (game->view.dir_y * sd->proj.spx
			- game->view.dir_x * sd->proj.spy);
	sd->proj.transy = sd->proj.inv * (-game->view.povy * sd->proj.spx
			+ game->view.povx * sd->proj.spy);
	sd->box.bob = (int)(sin((game->frame + (i * 20)) * 0.08) * 12.0);
	sd->box.sph = abs_int((int)(HEIGHT / sd->proj.transy));
	sd->box.spw = abs_int((int)(HEIGHT / sd->proj.transy));
	sd->box.spx0 = -sd->box.spw / 2 + (int)((WIDTH / 2)
			* (1 + sd->proj.transx / sd->proj.transy));
	sd->box.spx1 = sd->box.spw / 2 + (int)((WIDTH / 2)
			* (1 + sd->proj.transx / sd->proj.transy));
	sd->box.spy0 = -sd->box.sph / 2 + HEIGHT / 2 + sd->box.bob;
	sd->box.spy1 = sd->box.sph / 2 + HEIGHT / 2 + sd->box.bob;
}

static void	clamp_sprite_draw(t_spritedraw *sd)
{
	if (sd->box.spx0 < 0)
		sd->box.spx0 = 0;
	if (sd->box.spx1 >= WIDTH)
		sd->box.spx1 = WIDTH - 1;
	if (sd->box.spy0 < 0)
		sd->box.spy0 = 0;
	if (sd->box.spy1 >= HEIGHT)
		sd->box.spy1 = HEIGHT - 1;
}

static void	paint_sprite_column(t_game *game, t_spritedraw *sd)
{
	sd->y = sd->box.spy0;
	while (sd->y <= sd->box.spy1)
	{
		sd->tex_y = ((sd->y - sd->box.spy0)
				* game->tex.sprite.height) / sd->box.sph;
		sd->color = get_img_pixel(&game->tex.sprite, sd->tex_x, sd->tex_y);
		if ((sd->color & 0xFF000000) == 0)
			put_pixel(&game->img, sd->x, sd->y, sd->color);
		sd->y++;
	}
}

static void	draw_sprite(t_game *game, int i)
{
	t_spritedraw	sd;

	init_sprite_draw(game, i, &sd);
	if (sd.proj.transy <= 0)
		return ;
	clamp_sprite_draw(&sd);
	sd.x = sd.box.spx0;
	while (sd.x <= sd.box.spx1)
	{
		sd.tex_x = ((sd.x - sd.box.spx0) * game->tex.sprite.width)
			/ sd.box.spw;
		if (sd.proj.transy < game->zbuf[sd.x])
			paint_sprite_column(game, &sd);
		sd.x++;
	}
}

void	render_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.sprite_count)
	{
		game->sprites[i].dist = ((game->view.pos_x - game->sprites[i].x)
				* (game->view.pos_x - game->sprites[i].x))
			+ ((game->view.pos_y - game->sprites[i].y)
				* (game->view.pos_y - game->sprites[i].y));
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
