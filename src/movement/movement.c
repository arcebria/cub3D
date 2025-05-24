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
	if (game->map->map[(int)pos_y][(int)pos_x] != '1')
		return (1);
	return (0);
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


void	set_camera(t_game *game, mlx_key_data_t keydata, double rot_speed)
{
	if (keydata.key == MLX_KEY_RIGHT)
		rotate_camera(game, rot_speed);
	if (keydata.key == MLX_KEY_LEFT)
		rotate_camera(game, -rot_speed);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static double	last_x = SCREEN_WIDTH / 2;
	double			delta_x;
	(void) ypos;
	game = (t_game *)param;
	delta_x = xpos - last_x;

	if (delta_x > 2)
		rotate_camera(game, 0.01);
	else if (delta_x < -2)
		rotate_camera(game, -0.01);

	last_x = xpos;

	// Opcional: para que el ratón no se escape de la ventana
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
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
