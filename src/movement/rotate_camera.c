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

void	set_camera(t_game *game, mlx_key_data_t keydata, double rot_speed)
{
	if (keydata.key == MLX_KEY_RIGHT)
		rotate_camera(game, rot_speed);
	if (keydata.key == MLX_KEY_LEFT)
		rotate_camera(game, -rot_speed);
}

//mouse_pos se utiliza para evitar que el cursor salga de la ventana

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static double	last_x;
	double			delta_x;

	(void) ypos;
	last_x = SCREEN_WIDTH / 2;
	game = (t_game *)param;
	delta_x = xpos - last_x;
	if (delta_x > 2)
		rotate_camera(game, 0.01);
	else if (delta_x < -2)
		rotate_camera(game, -0.01);
	last_x = xpos;
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
}
