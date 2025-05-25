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

int	is_walkable(t_game *game, double pos_x, double pos_y)
{
	double	x_start;
	double	x_end;
	double	y_start;
	double	y_end;

	x_start = pos_x - BUFFER;
	x_end = pos_x + BUFFER;
	y_start = pos_y - BUFFER;
	y_end = pos_y + BUFFER;
	while (x_start <= x_end)
	{
		while (y_start <= y_end)
		{
			if (game->map->map[(int)y_start][(int)x_start] == '1')
				return (0);
			y_start += BUFFER;
		}
		x_start += BUFFER;
	}
	return (1);
}

void	move_forward_back(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (is_walkable(game, game->pos_x + game->dir_x
				* MOVE_SPEED, game->pos_y))
			game->pos_x += game->dir_x * MOVE_SPEED;
		if (is_walkable(game, game->pos_x, game->pos_y
				+ game->dir_y * MOVE_SPEED))
			game->pos_y += game->dir_y * MOVE_SPEED;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (is_walkable(game, game->pos_x - game->dir_x
				* MOVE_SPEED, game->pos_y))
			game->pos_x -= game->dir_x * MOVE_SPEED;
		if (is_walkable(game, game->pos_x, game->pos_y
				- game->dir_y * MOVE_SPEED))
			game->pos_y -= game->dir_y * MOVE_SPEED;
	}
}

void	move_right_left(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_D)
	{
		if (is_walkable(game, game->pos_x + game->plane_x
				* MOVE_SPEED, game->pos_y))
			game->pos_x += game->plane_x * MOVE_SPEED;
		if (is_walkable(game, game->pos_x, game->pos_y
				+ game->plane_y * MOVE_SPEED))
			game->pos_y += game->plane_y * MOVE_SPEED;
	}
	if (keydata.key == MLX_KEY_A)
	{
		if (is_walkable(game, game->pos_x - game->plane_x
				* MOVE_SPEED, game->pos_y))
			game->pos_x -= game->plane_x * MOVE_SPEED;
		if (is_walkable(game, game->pos_x, game->pos_y
				- game->plane_y * MOVE_SPEED))
			game->pos_y -= game->plane_y * MOVE_SPEED;
	}
}

void	movement(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		move_forward_back(game, keydata);
		move_right_left(game, keydata);
		set_camera(game, keydata, ROT_SPEED);
		animation(game, keydata);
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(game->mlx);
			exit(0);
		}
	}
}
