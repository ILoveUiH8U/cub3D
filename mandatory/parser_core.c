/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:18:35 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:35:15 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(*game));
	game->map.player_x = -1;
	game->map.player_y = -1;
}

static void	p_error(char *err)
{
	ft_putendl_fd("Error", 2);
	if (err)
		ft_putendl_fd(err, 2);
	free(err);
}

static int	p_die(t_game *game, t_scene *scene, char *err)
{
	p_free_lines(scene->lines, scene->count);
	free_game(game);
	p_error(err);
	return (0);
}

int	p_has_cub(char *path)
{
	int	len;

	len = ft_strlen(path);
	return (len > 4 && ft_strcmp(path + len - 4, ".cub") == 0);
}

int	parse_cub_file(const char *path, t_game *game)
{
	t_scene	scene;
	char	*err;

	if (!p_has_cub((char *)path))
		return (p_error(ft_strdup("Expected a .cub file")), 0);
	err = NULL;
	ft_memset(&scene, 0, sizeof(scene));
	scene.err = &err;
	if (!p_read_file((char *)path, &scene))
		return (p_error(err), 0);
	if (!p_read_config(game, &scene))
		return (p_die(game, &scene, err));
	if (!p_build_map(game, &scene))
		return (p_die(game, &scene, err));
	p_free_lines(scene.lines, scene.count);
	return (1);
}
