/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:14:23 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/28 20:44:10 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D map.cub", 2);
		return (1);
	}
	init_game(&game);
	if (!parse_cub_file(argv[1], &game))
		return (1);
	ft_putendl_fd("Map parsed successfully", 1);
	free_game(&game);
	return (0);
}
