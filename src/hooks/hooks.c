/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:37:45 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/28 17:43:40 by arcebria         ###   ########.fr       */
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

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	close_door(t_game *game, int front_x, int front_y)
{
	float	door_center_x;
	float	door_center_y;
	float	distance;

	door_center_x = front_x + 0.5f;
	door_center_y = front_y + 0.5f;
	distance = calculate_distance(game->pos_x, game->pos_y,
			door_center_x, door_center_y);
	if (distance > 0.7f)
		game->map->map[front_y][front_x] = 'p';
}

void	door_interaction(t_game *game)
{
	int	front_x;
	int	front_y;
	int	cell;

	front_x = (int)(game->pos_x + game->dir_x * 1);
	front_y = (int)(game->pos_y + game->dir_y * 1);
	if (front_x >= 0 && front_x < game->map->map_width
		&& front_y >= 0 && front_y < game->map->map_height)
	{
		cell = game->map->map[front_y][front_x];
		if (cell == 'p')
			game->map->map[front_y][front_x] = '2';
		else if (cell == '2')
			close_door(game, front_x, front_y);
	}
}

void	hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		animation(game, keydata);
		if (keydata.key == MLX_KEY_SPACE)
			door_interaction(game);
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(game->mlx);
			exit(0);
		}
	}
}
