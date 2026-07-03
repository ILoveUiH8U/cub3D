/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:35:30 by mnajem            #+#    #+#             */
/*   Updated: 2026/04/02 21:02:25 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img *img, t_minipos pos, int size, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(img, pos.x + i, pos.y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_texture_square(t_img *img, t_img *tex,
	t_minipos pos, int size)
{
	int	i;
	int	j;
	int	tex_x;
	int	tex_y;

	j = 0;
	while (j < size)
	{
		i = 0;
		tex_y = (j * tex->height) / size;
		while (i < size)
		{
			tex_x = (i * tex->width) / size;
			put_pixel(img, pos.x + i, pos.y + j,
				get_img_pixel(tex, tex_x, tex_y));
			i++;
		}
		j++;
	}
}

static int	get_tile_color(t_minidata *mm, t_minipos map)
{
	char	tile;

	if (map.y < 0 || map.y >= mm->game->map.height
		|| map.x < 0 || map.x >= mm->game->map.width)
		return (-1);
	tile = mm->game->map.grid[map.y][map.x];
	if (tile == '1' || tile == 'D')
		return (MM_WALL_COLOR);
	if (tile == '0' || tile == 'K' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W')
		return (MM_FLOOR_COLOR);
	return (-1);
}

static void	draw_map_tile(t_minidata *mm, t_minipos map)
{
	int			color;
	t_minipos	screen;
	char		tile;

	if (map.y < 0 || map.y >= mm->game->map.height
		|| map.x < 0 || map.x >= mm->game->map.width)
		return ;
	tile = mm->game->map.grid[map.y][map.x];
	screen.x = mm->center.x + (int)((map.x - mm->game->view.pos_x) * MM_TILE);
	screen.y = mm->center.y + (int)((map.y - mm->game->view.pos_y) * MM_TILE);
	if (tile == 'D')
	{
		draw_texture_square(&mm->game->img, &mm->game->tex.door,
			screen, MM_TILE - 1);
		return ;
	}
	color = get_tile_color(mm, map);
	if (color == -1)
		return ;
	draw_square(&mm->game->img, screen, MM_TILE - 1, color);
}

void	draw_minimap_tiles(t_minidata *mm)
{
	t_minipos	map;

	map.y = (int)mm->game->view.pos_y - MM_RADIUS;
	while (map.y <= (int)mm->game->view.pos_y + MM_RADIUS)
	{
		map.x = (int)mm->game->view.pos_x - MM_RADIUS;
		while (map.x <= (int)mm->game->view.pos_x + MM_RADIUS)
		{
			draw_map_tile(mm, map);
			map.x++;
		}
		map.y++;
	}
}
