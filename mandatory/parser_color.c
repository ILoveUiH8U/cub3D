/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:04:23 by haabu-sa          #+#    #+#             */
/*   Updated: 2026/06/24 19:35:49 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	p_skip_space(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13)))
		(*i)++;
}

int	p_set_error(char **err, char *msg)
{
	if (err)
		*err = ft_strdup(msg);
	return (0);
}

static int	p_rgb_part(char *value, int *i, int *out)
{
	long	n;

	if (!ft_isdigit((unsigned char)value[*i]))
		return (0);
	n = 0;
	while (ft_isdigit((unsigned char)value[*i]))
	{
		n = (n * 10) + (value[*i] - '0');
		if (n > 255)
			return (0);
		(*i)++;
	}
	*out = (int)n;
	return (1);
}

int	p_save_rgb(char *value, int *dst, int *flag, char **err)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (*flag)
		return (p_set_error(err, "Duplicate color identifier"));
	i = 0;
	p_skip_space(value, &i);
	if (!p_rgb_part(value, &i, &r) || value[i++] != ',')
		return (p_set_error(err, "Invalid RGB color format"));
	if (!p_rgb_part(value, &i, &g) || value[i++] != ',')
		return (p_set_error(err, "Invalid RGB color format"));
	if (!p_rgb_part(value, &i, &b))
		return (p_set_error(err, "Invalid RGB color format"));
	p_skip_space(value, &i);
	if (value[i])
		return (p_set_error(err, "Extra characters in RGB color"));
	*dst = (r << 16) | (g << 8) | b;
	*flag = 1;
	return (1);
}

int	p_save_texture(char **dst, char *value, char **err)
{
	char	*path;
	int		end;

	if (*dst)
		return (p_set_error(err, "Duplicate texture identifier"));
	end = ft_strlen(value);
	while (end > 0 && (value[end - 1] == ' '
			|| (value[end - 1] >= 9 && value[end - 1] <= 13)))
		end--;
	if (end == 0)
		return (p_set_error(err, "Texture path is empty"));
	path = malloc((size_t)end + 1);
	if (!path)
		return (p_set_error(err, "Out of memory while storing texture path"));
	ft_memcpy(path, value, end);
	path[end] = '\0';
	if (!p_readable_file(path))
	{
		free(path);
		return (p_set_error(err, "Texture file not readable"));
	}
	*dst = path;
	return (1);
}
