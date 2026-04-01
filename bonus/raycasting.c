/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:00:06 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/01 17:53:05 by mnajem           ###   ########.fr       */
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

static void	init_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->v.dir_x < 0)
	{
		ray->sx = -1;
		ray->v.sdx = (game->pos_x - ray->mx) * ray->v.ddx;
	}
	else
	{
		ray->sx = 1;
		ray->v.sdx = (ray->mx + 1.0 - game->pos_x) * ray->v.ddx;
	}
	if (ray->v.dir_y < 0)
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

static void	run_dda(t_game *game, t_ray *ray)
{
	while (1)
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
		if (game->map.grid[ray->my][ray->mx] == '1')
			return ;
	}
}

static void	get_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->v.dist = ray->v.sdx - ray->v.ddx;
	else
		ray->v.dist = ray->v.sdy - ray->v.ddy;
}

static void	set_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->v.dir_x > 0)
			ray->tex = &game->tex.we;
		else
			ray->tex = &game->tex.ea;
	}
	else
	{
		if (ray->v.dir_y > 0)
			ray->tex = &game->tex.no;
		else
			ray->tex = &game->tex.so;
	}
}

static void	draw_wall(t_game *game, t_ray *ray)
{
	int	h;
	int	start;
	int	end;

	if (ray->v.dist <= 0.0)
		return ;
	h = (int)(HEIGHT / ray->v.dist);
	start = -h / 2 + HEIGHT / 2;
	end = h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	set_wall_texture(game, ray);
	draw_vertical_line(game, ray, start, end);
}

static void	cast_a_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, &ray, x);
	init_dda(game, &ray);
	init_step_and_side(game, &ray);
	run_dda(game, &ray);
	get_wall_dist(&ray);
	draw_wall(game, &ray);
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
