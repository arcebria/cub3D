/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:37:45 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 20:04:43 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	is_walkable(t_game *game, int pos_x, int pos_y)
{
	if (game->map->map[(int)pos_y][(int)pos_x] != '1')
		return (1);
	return (0);
}

void	movement(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
		{
			if (is_walkable(game, game->pos_x + game->dir_x * MOVE_SPEED, game->pos_y))
				game->pos_x += game->dir_x * MOVE_SPEED;
			if (is_walkable(game, game->pos_x, game->pos_y + game->dir_y * MOVE_SPEED))
				game->pos_y += game->dir_y * MOVE_SPEED;
		}
	}
}
