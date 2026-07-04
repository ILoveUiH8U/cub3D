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
	t_sprite_proj	*p;
	t_sprite_box	*b;
	t_view			*v;
	int				screen_x;

	p = &sd->proj;
	b = &sd->box;
	v = &game->view;
	p->spx = game->sprites[i].x - v->pos_x;
	p->spy = game->sprites[i].y - v->pos_y;
	p->inv = 1.0 / (v->povx * v->dir_y - v->dir_x * v->povy);
	p->transx = p->inv * (v->dir_y * p->spx - v->dir_x * p->spy);
	p->transy = p->inv * (-v->povy * p->spx + v->povx * p->spy);
	b->bob = (int)(sin((game->frame + (i * 20)) * 0.08) * 12.0);
	b->sph = abs_int((int)(HEIGHT / p->transy));
	b->spw = b->sph;
	screen_x = (int)((WIDTH / 2) * (1 + p->transx / p->transy));
	b->spx0 = screen_x - b->spw / 2;
	b->spx1 = screen_x + b->spw / 2;
	b->spy0 = -b->sph / 2 + HEIGHT / 2 + b->bob;
	b->spy1 = b->sph / 2 + HEIGHT / 2 + b->bob;
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
