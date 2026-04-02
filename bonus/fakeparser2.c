#include "cub3d.h"

static int	set_error(char **err_msg, const char *msg)
{
	if (err_msg)
		*err_msg = ft_strdup((char *)msg);
	return (0);
}

static int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_allowed_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'D' || c == ' ' || is_player(c));
}

static void	free_grid_rows(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	destroy_img(void *mlx, t_img *img)
{
	if (mlx && img->img)
		mlx_destroy_image(mlx, img->img);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	free_game(t_game *game)
{
	int	i;

	free(game->cfg.no_path);
	free(game->cfg.so_path);
	free(game->cfg.we_path);
	free(game->cfg.ea_path);
	game->cfg.no_path = NULL;
	game->cfg.so_path = NULL;
	game->cfg.we_path = NULL;
	game->cfg.ea_path = NULL;
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = 0;
	destroy_img(game->mlx, &game->tex.no);
	destroy_img(game->mlx, &game->tex.so);
	destroy_img(game->mlx, &game->tex.we);
	destroy_img(game->mlx, &game->tex.ea);
	destroy_img(game->mlx, &game->tex.door);
	destroy_img(game->mlx, &game->img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->mlx = NULL;
}

static int	count_map_rows(char **lines, int start, int count)
{
	int	i;
	int	rows;

	i = start;
	rows = 0;
	while (i < count)
	{
		if (is_empty_line(lines[i]))
			break ;
		rows++;
		i++;
	}
	while (i < count)
	{
		if (!is_empty_line(lines[i]))
			return (-1);
		i++;
	}
	return (rows);
}

static int	map_max_width(char **lines, int start, int rows)
{
	int	i;
	int	w;
	int	maxw;

	i = 0;
	maxw = 0;
	while (i < rows)
	{
		w = ft_strlen(lines[start + i]);
		if (w > maxw)
			maxw = w;
		i++;
	}
	return (maxw);
}

static int	build_grid(t_game *game, char **lines, int start, int rows)
{
	int	i;
	int	len;

	game->map.grid = malloc(sizeof(char *) * rows);
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i < rows)
	{
		game->map.grid[i] = malloc((size_t)game->map.width + 1);
		if (!game->map.grid[i])
			return (free_grid_rows(game->map.grid, i), game->map.grid = NULL, 0);
		ft_memset(game->map.grid[i], ' ', game->map.width);
		game->map.grid[i][game->map.width] = '\0';
		len = ft_strlen(lines[start + i]);
		if (len > 0)
			ft_memcpy(game->map.grid[i], lines[start + i], len);
		i++;
	}
	return (1);
}

static int	validate_chars_and_player(t_game *game, char **err_msg)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!is_allowed_map_char(game->map.grid[y][x]))
				return (set_error(err_msg, "Invalid character in map"));
			if (is_player(game->map.grid[y][x]))
			{
				player_count++;
				game->map.player_x = x;
				game->map.player_y = y;
				game->map.player_dir = game->map.grid[y][x];
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (set_error(err_msg, "Map must contain exactly one player"));
	return (1);
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'D' || is_player(c));
}

static int	is_open_around(t_game *game, int x, int y)
{
	if (x == 0 || y == 0 || x == game->map.width - 1 || y == game->map.height - 1)
		return (1);
	if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y + 1][x] == ' '
		|| game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

static int	validate_closed_map(t_game *game, char **err_msg)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_walkable(game->map.grid[y][x]) && is_open_around(game, x, y))
				return (set_error(err_msg, "Map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (1);
}

int	build_and_validate_map(t_game *game, t_mapbuild *build)
{
	int	rows;

	rows = count_map_rows(build->lines, build->start, build->count);
	if (rows < 0)
		return (set_error(build->err_msg, "Empty line inside map is not allowed"));
	if (rows == 0)
		return (set_error(build->err_msg, "Map section is missing"));
	game->map.height = rows;
	game->map.width = map_max_width(build->lines, build->start, rows);
	if (game->map.width <= 0)
		return (set_error(build->err_msg, "Map width is invalid"));
	if (!build_grid(game, build->lines, build->start, rows))
		return (set_error(build->err_msg, "Out of memory while building map"));
	if (!validate_chars_and_player(game, build->err_msg))
		return (0);
	if (!validate_closed_map(game, build->err_msg))
		return (0);
	return (1);
}
