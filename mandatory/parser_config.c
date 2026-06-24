/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:21:53 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:35:29 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	p_take_id(char *line, int *i, char id[3])
{
	p_skip_space(line, i);
	id[0] = line[(*i)++];
	id[1] = '\0';
	id[2] = '\0';
	if (line[*i] && !(line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13)))
		id[1] = line[(*i)++];
	p_skip_space(line, i);
}

static int	p_set_texture(t_game *game, char *id, char *value, char **err)
{
	if (ft_strcmp(id, "NO") == 0)
		return (p_save_texture(&game->cfg.no_path, value, err));
	if (ft_strcmp(id, "SO") == 0)
		return (p_save_texture(&game->cfg.so_path, value, err));
	if (ft_strcmp(id, "WE") == 0)
		return (p_save_texture(&game->cfg.we_path, value, err));
	if (ft_strcmp(id, "EA") == 0)
		return (p_save_texture(&game->cfg.ea_path, value, err));
	return (-1);
}

static int	p_set_color(t_game *game, char *id, char *value, char **err)
{
	if (ft_strcmp(id, "F") == 0)
		return (p_save_rgb(value, &game->cfg.floor_color,
				&game->cfg.has_floor, err));
	if (ft_strcmp(id, "C") == 0)
		return (p_save_rgb(value, &game->cfg.ceil_color,
				&game->cfg.has_ceil, err));
	return (-1);
}

static int	p_config_line(t_game *game, char *line, int *read, char **err)
{
	char	id[3];
	int		i;
	int		status;

	i = 0;
	if (p_is_blank(line))
		return (1);
	p_take_id(line, &i, id);
	if (!line[i])
		return (p_set_error(err, "Configuration value is missing"));
	status = p_set_texture(game, id, line + i, err);
	if (status == -1)
		status = p_set_color(game, id, line + i, err);
	if (status == 1)
		(*read)++;
	if (status == -1)
		return (p_set_error(err, "Unknown identifier in configuration"));
	return (status);
}

int	p_read_config(t_game *game, t_scene *scene)
{
	int	i;
	int	read;

	i = 0;
	read = 0;
	while (i < scene->count && read < 6)
	{
		if (!p_config_line(game, scene->lines[i], &read, scene->err))
			return (0);
		i++;
	}
	if (read < 6)
		return (p_set_error(scene->err, "Missing required configuration"));
	while (i < scene->count && p_is_blank(scene->lines[i]))
		i++;
	scene->start = i;
	return (1);
}
