/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:35:01 by mnajem            #+#    #+#             */
/*   Updated: 2026/06/24 20:35:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_texture(t_game *game, t_ray *ray)
{
	if (game->map.grid[ray->my][ray->mx] == 'D'
		&& !game->map.door_open[ray->my][ray->mx])
		ray->tex = &game->tex.door;
	else if (ray->side == 0 && ray->v.dir_x > 0)
		ray->tex = &game->tex.we;
	else if (ray->side == 0)
		ray->tex = &game->tex.ea;
	else if (ray->v.dir_y > 0)
		ray->tex = &game->tex.no;
	else
		ray->tex = &game->tex.so;
}

static void	set_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->v.dist = ray->v.sdx - ray->v.ddx;
	else
		ray->v.dist = ray->v.sdy - ray->v.ddy;
}

void	draw_ray(t_game *game, t_ray *ray)
{
	int	h;
	int	start;
	int	end;

	set_wall_dist(ray);
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
	run_dda(game, &ray);
	draw_ray(game, &ray);
	game->zbuf[x] = ray.v.dist;
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
		cast_a_ray(game, x++);
}
