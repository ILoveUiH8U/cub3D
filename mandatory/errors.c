/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:08:50 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/29 20:09:01 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

void	cleanup_and_exit(t_game *game, char *msg)
{
	free_game(game);
	error_exit(msg);
}
