/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:05:07 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:34:41 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	p_is_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

static int	p_count_rows(t_scene *scene)
{
	int	i;
	int	rows;

	i = scene->start;
	rows = 0;
	while (i < scene->count && !p_is_blank(scene->lines[i]))
	{
		rows++;
		i++;
	}
	while (i < scene->count)
	{
		if (!p_is_blank(scene->lines[i]))
			return (-1);
		i++;
	}
	return (rows);
}

static int	p_max_width(t_scene *scene, int rows)
{
	int	i;
	int	width;
	int	line_width;

	i = 0;
	width = 0;
	while (i < rows)
	{
		line_width = ft_strlen(scene->lines[scene->start + i]);
		if (line_width > width)
			width = line_width;
		i++;
	}
	return (width);
}

static int	p_copy_grid_row(t_game *game, t_scene *scene, int y)
{
	int	len;

	game->map.grid[y] = malloc((size_t)game->map.width + 1);
	if (!game->map.grid[y])
		return (0);
	ft_memset(game->map.grid[y], ' ', game->map.width);
	game->map.grid[y][game->map.width] = '\0';
	len = ft_strlen(scene->lines[scene->start + y]);
	if (len > 0)
		ft_memcpy(game->map.grid[y], scene->lines[scene->start + y], len);
	return (1);
}

int	p_build_map(t_game *game, t_scene *scene)
{
	int	rows;
	int	y;

	rows = p_count_rows(scene);
	if (rows < 0)
		return (p_set_error(scene->err,
				"Empty line inside map is not allowed"));
	if (rows == 0)
		return (p_set_error(scene->err, "Map section is missing"));
	game->map.height = rows;
	game->map.width = p_max_width(scene, rows);
	game->map.grid = ft_calloc(rows, sizeof(char *));
	if (!game->map.grid)
		return (p_set_error(scene->err, "Out of memory while building map"));
	y = 0;
	while (y < rows)
	{
		if (!p_copy_grid_row(game, scene, y))
			return (p_set_error(scene->err,
					"Out of memory while building map"));
		y++;
	}
	return (p_validate_map(game, scene->err));
}
