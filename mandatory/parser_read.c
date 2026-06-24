/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:05:15 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:34:22 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	p_free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(lines[i++]);
	free(lines);
}

static char	*p_trim_eol(char *line)
{
	char	*clean;
	int		len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	clean = malloc((size_t)len + 1);
	if (!clean)
		return (NULL);
	ft_memcpy(clean, line, len);
	clean[len] = '\0';
	return (clean);
}

static int	p_push_line(t_scene *scene, char *line)
{
	char	**next;
	int		i;

	next = malloc(sizeof(char *) * (scene->count + 1));
	if (!next)
		return (0);
	i = 0;
	while (i < scene->count)
	{
		next[i] = scene->lines[i];
		i++;
	}
	next[i] = line;
	free(scene->lines);
	scene->lines = next;
	scene->count++;
	return (1);
}

static int	p_read_loop(int fd, t_scene *scene)
{
	char	*line;
	char	*clean;

	line = get_next_line(fd);
	while (line)
	{
		clean = p_trim_eol(line);
		free(line);
		if (!clean || !p_push_line(scene, clean))
		{
			free(clean);
			return (p_set_error(scene->err,
					"Out of memory while reading file"));
		}
		line = get_next_line(fd);
	}
	return (1);
}

int	p_read_file(char *path, t_scene *scene)
{
	int	fd;
	int	ok;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (p_set_error(scene->err, "Could not open .cub file"));
	ok = p_read_loop(fd, scene);
	close(fd);
	return (ok);
}
