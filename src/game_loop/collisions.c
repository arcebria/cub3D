/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:37:45 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/23 22:08:38 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	is_wall(t_game *game, double x, double y)
{
	if (game->map->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int	is_walkable(t_game *game, double pos_x, double pos_y)
{
	double	x;
	double	y;

	x = pos_x - BUFFER;
	while (x <= pos_x + BUFFER)
	{
		y = pos_y - BUFFER;
		while (y <= pos_y + BUFFER)
		{
			if (is_wall(game, x, y))
				return (0);
			y += BUFFER;
		}
		x += BUFFER;
	}
	return (1);
}
