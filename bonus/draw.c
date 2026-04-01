/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:16:31 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/01 17:52:59 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	    return ;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;

}

static int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

static int	get_tex_x(t_game *g, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = g->pos_y + ray->v.dist * ray->v.dir_y;
	else
		wall_x = g->pos_x + ray->v.dist * ray->v.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * ray->tex->width);
	if ((ray->side == 0 && ray->v.dir_x > 0)
		|| (ray->side == 1 && ray->v.dir_y < 0))
		tex_x = ray->tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->tex->width)
		tex_x = ray->tex->width - 1;
	return (tex_x);
}

static void	draw_texture_pixels(t_game *g, t_ray *ray, int start, int end,
		int tex_x)
{
	int		y;
	int		line_h;
	int		tex_y;
	double	step;
	double	tex_pos;

	line_h = (int)(HEIGHT / ray->v.dist);
	step = (double)ray->tex->height / line_h;
	tex_pos = (start - HEIGHT / 2 + line_h / 2) * step;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray->tex->height)
			tex_y = ray->tex->height - 1;
		put_pixel(&g->img, ray->x, y,
		get_texture_pixel(ray->tex, tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}

void draw_vertical_line(t_game *g, t_ray *ray, int start, int end)
{
	int	tex_x;

	tex_x = get_tex_x(g, ray);
	draw_texture_pixels(g, ray, start, end, tex_x);
}
