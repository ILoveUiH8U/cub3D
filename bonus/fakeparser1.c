#include "cub3d.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*dup_without_newline(const char *line)
{
	int		len;
	char	*out;

	len = ft_strlen((char *)line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	out = malloc((size_t)len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, (void *)line, len);
	out[len] = '\0';
	return (out);
}

static void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	set_error(char **err_msg, const char *msg)
{
	if (err_msg)
		*err_msg = ft_strdup((char *)msg);
	return (0);
}

static int	append_line(char ***lines, int *count, int *cap, char *line)
{
	char	**new_lines;
	int		i;

	if (*count >= *cap)
	{
		if (*cap == 0)
			*cap = 16;
		else
			*cap *= 2;
		new_lines = malloc(sizeof(char *) * (*cap));
		if (!new_lines)
			return (0);
		i = 0;
		while (i < *count)
		{
			new_lines[i] = (*lines)[i];
			i++;
		}
		free(*lines);
		*lines = new_lines;
	}
	(*lines)[*count] = line;
	(*count)++;
	return (1);
}

static int	read_all_lines(const char *path, char ***lines_out, int *count_out,
		char **err_msg)
{
	int		fd;
	char	*line;
	char	*clean;
	char	**lines;
	int		count;
	int		cap;

	lines = NULL;
	count = 0;
	cap = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (set_error(err_msg, "Could not open .cub file"));
	line = get_next_line(fd);
	while (line)
	{
		clean = dup_without_newline(line);
		free(line);
		if (!clean || !append_line(&lines, &count, &cap, clean))
		{
			close(fd);
			free_lines(lines, count);
			return (set_error(err_msg, "Out of memory while reading file"));
		}
		line = get_next_line(fd);
	}
	close(fd);
	*lines_out = lines;
	*count_out = count;
	return (1);
}

static int	has_cub_extension(const char *path)
{
	int	len;

	len = ft_strlen((char *)path);
	return (len > 4 && ft_strcmp(path + len - 4, ".cub") == 0);
}

static void	skip_spaces(const char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

static int	parse_texture(char **dst, const char *value, char **err_msg)
{
	int		end;
	char	*path;

	if (*dst)
		return (set_error(err_msg, "Duplicate texture identifier"));
	end = ft_strlen((char *)value);
	while (end > 0 && is_space(value[end - 1]))
		end--;
	if (end == 0)
		return (set_error(err_msg, "Texture path is empty"));
	path = malloc((size_t)end + 1);
	if (!path)
		return (set_error(err_msg, "Out of memory while storing texture path"));
	ft_memcpy(path, (void *)value, end);
	path[end] = '\0';
	if (access(path, R_OK) != 0)
	{
		free(path);
		return (set_error(err_msg, "Texture file not found or unreadable"));
	}
	*dst = path;
	return (1);
}

static int	parse_color_component(const char *s, int *i, int *out)
{
	long	value;

	skip_spaces(s, i);
	if (!ft_isdigit((unsigned char)s[*i]))
		return (0);
	value = 0;
	while (ft_isdigit((unsigned char)s[*i]))
	{
		value = value * 10 + (s[*i] - '0');
		if (value > 255)
			return (0);
		(*i)++;
	}
	skip_spaces(s, i);
	*out = (int)value;
	return (1);
}

static int	parse_rgb(const char *value, int *dst, int *is_set, char **err_msg)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (*is_set)
		return (set_error(err_msg, "Duplicate color identifier"));
	i = 0;
	if (!parse_color_component(value, &i, &r) || value[i++] != ','
		|| !parse_color_component(value, &i, &g) || value[i++] != ','
		|| !parse_color_component(value, &i, &b))
		return (set_error(err_msg, "Invalid RGB color format"));
	skip_spaces(value, &i);
	if (value[i] != '\0')
		return (set_error(err_msg, "Extra characters in RGB color"));
	*dst = (r << 16) | (g << 8) | b;
	*is_set = 1;
	return (1);
}

static int	parse_config_line(t_game *game, const char *line, int *parsed,
		char **err_msg)
{
	int		i;
	char	id[3];

	i = 0;
	skip_spaces(line, &i);
	if (!line[i])
		return (1);
	id[0] = line[i++];
	id[1] = '\0';
	id[2] = '\0';
	if (line[i] && !is_space(line[i]))
		id[1] = line[i++];
	skip_spaces(line, &i);
	if (!line[i])
		return (set_error(err_msg, "Configuration value is missing"));
	if (ft_strcmp(id, "NO") == 0
		&& parse_texture(&game->cfg.no_path, line + i,
			err_msg))
		return ((*parsed)++, 1);
	if (ft_strcmp(id, "SO") == 0
		&& parse_texture(&game->cfg.so_path, line + i,
			err_msg))
		return ((*parsed)++, 1);
	if (ft_strcmp(id, "WE") == 0
		&& parse_texture(&game->cfg.we_path, line + i,
			err_msg))
		return ((*parsed)++, 1);
	if (ft_strcmp(id, "EA") == 0
		&& parse_texture(&game->cfg.ea_path, line + i,
			err_msg))
		return ((*parsed)++, 1);
	if (ft_strcmp(id, "F") == 0
		&& parse_rgb(line + i, &game->cfg.floor_color,
			&game->cfg.has_floor, err_msg))
		return ((*parsed)++, 1);
	if (ft_strcmp(id, "C") == 0
		&& parse_rgb(line + i, &game->cfg.ceil_color,
			&game->cfg.has_ceil, err_msg))
		return ((*parsed)++, 1);
	if (*err_msg)
		return (0);
	return (set_error(err_msg, "Unknown identifier in configuration"));
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(*game));
	game->map.player_x = -1;
	game->map.player_y = -1;
}

static void	print_error_and_free(char *err_msg)
{
	ft_putendl_fd("Error", 2);
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free(err_msg);
}

int	parse_cub_file(const char *path, t_game *game)
{
	char	**lines;
	char	*err_msg;
	int		count;
	int		i;
	int		parsed;
	t_mapbuild	build;

	if (!has_cub_extension(path))
		return (print_error_and_free(ft_strdup("Expected a .cub file")), 0);
	err_msg = NULL;
	if (!read_all_lines(path, &lines, &count, &err_msg))
		return (print_error_and_free(err_msg), 0);
	i = 0;
	parsed = 0;
	while (i < count && parsed < 6)
	{
		if (!is_empty_line(lines[i]) && !parse_config_line(game, lines[i], &parsed,
				&err_msg))
			return (free_lines(lines, count), free_game(game),
				print_error_and_free(err_msg), 0);
		i++;
	}
	if (parsed < 6)
		return (free_lines(lines, count), free_game(game),
			print_error_and_free(ft_strdup("Missing required configuration")), 0);
	while (i < count && is_empty_line(lines[i]))
		i++;
	build.lines = lines;
	build.start = i;
	build.count = count;
	build.err_msg = &err_msg;
	if (!build_and_validate_map(game, &build))
		return (free_lines(lines, count), free_game(game),
			print_error_and_free(err_msg), 0);
	free_lines(lines, count);
	return (1);
}
