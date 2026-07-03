/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:14:23 by mnajem            #+#    #+#             */
/*   Updated: 2026/07/04 02:07:46 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
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
	init_player(&game);
	init_mlx(&game);
	load_textures(&game);
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img.img)
		cleanup_and_exit(&game, "mlx_new_image failed");
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.line_len, &game.img.endian);
	if (!game.img.addr)
		cleanup_and_exit(&game, "mlx_get_data_addr failed");
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
