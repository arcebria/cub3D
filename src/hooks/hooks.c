/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:37:45 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/27 16:14:38 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
		rotate_camera(game, 0.025);
	else if (delta_x < -2)
		rotate_camera(game, -0.025);
	last_x = xpos;
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
}

void	hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		animation(game, keydata);
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(game->mlx);
			exit(0);
		}
	}
}
