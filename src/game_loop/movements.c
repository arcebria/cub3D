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

void	rotate_camera(t_game *game, double rot_speed)
{
	game->old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
	game->dir_y = game->old_dir_x * sin(rot_speed) + game->dir_y
		* cos(rot_speed);
	game->old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y
		* sin(rot_speed);
	game->plane_y = game->old_plane_x * sin(rot_speed)
		+ game->plane_y * cos(rot_speed);
}


void	move_forward(t_game *game)
{
	if (is_walkable(game, game->pos_x + game->dir_x
			* MOVE_SPEED, game->pos_y))
		game->pos_x += game->dir_x * MOVE_SPEED;
	if (is_walkable(game, game->pos_x, game->pos_y
			+ game->dir_y * MOVE_SPEED))
		game->pos_y += game->dir_y * MOVE_SPEED;
}

void	move_backward(t_game *game)
{
	if (is_walkable(game, game->pos_x - game->dir_x
			* MOVE_SPEED, game->pos_y))
		game->pos_x -= game->dir_x * MOVE_SPEED;
	if (is_walkable(game, game->pos_x, game->pos_y
			- game->dir_y * MOVE_SPEED))
		game->pos_y -= game->dir_y * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	if (is_walkable(game, game->pos_x + game->plane_x
			* MOVE_SPEED, game->pos_y))
		game->pos_x += game->plane_x * MOVE_SPEED;
	if (is_walkable(game, game->pos_x, game->pos_y
			+ game->plane_y * MOVE_SPEED))
		game->pos_y += game->plane_y * MOVE_SPEED;
}

void	move_left(t_game *game)
{
	if (is_walkable(game, game->pos_x - game->plane_x
			* MOVE_SPEED, game->pos_y))
		game->pos_x -= game->plane_x * MOVE_SPEED;
	if (is_walkable(game, game->pos_x, game->pos_y
			- game->plane_y * MOVE_SPEED))
		game->pos_y -= game->plane_y * MOVE_SPEED;
}
