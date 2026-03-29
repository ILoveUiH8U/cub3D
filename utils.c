/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:10:23 by mnajem            #+#    #+#             */
/*   Updated: 2026/03/29 20:11:14 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map)
{
    int i;

    i = 0;
    if (!map)
	    return ;
    while (map[i])
	    free(map[i++]);
    free(map);

}

int get_width(char *row)
{
    int i = 0;

    while (row[i] && row[i] != '\n')
	    i++;
    return (i);

}