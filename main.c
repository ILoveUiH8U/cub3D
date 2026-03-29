/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:14:23 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/29 20:19:02 by mnajem           ###   ########.fr       */
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
	t_game g;

	init_mlx(&g);
	
	g.img.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	g.img.addr = mlx_get_data_addr(g.img.img, &g.img.bpp,
			&g.img.line_len, &g.img.endian);
	
	mlx_loop_hook(g.mlx, render_frame, &g);
	mlx_loop(g.mlx);
	free_game(&game);
	return (0);
}
