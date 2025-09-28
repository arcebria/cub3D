/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/28 17:36:16 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	change_sprites(t_game *game)
{
	if (game->current_sprite == 1)
	{
		game->pistol1_img->enabled = false;
		game->pistol2_img->enabled = true;
		game->current_sprite = 2;
	}
	else if (game->current_sprite == 2)
	{
		game->pistol2_img->enabled = false;
		game->pistol3_img->enabled = true;
		game->current_sprite = 3;
	}
	else if (game->current_sprite == 3)
	{
		game->pistol3_img->enabled = false;
		game->pistol1_img->enabled = true;
		game->current_sprite = 1;
		game->is_animating = 0;
	}
}

void	animate_pistol(void *param)
{
	t_game					*game;
	static struct timeval	last_time;
	struct timeval			current_time;
	long					elapsed_time;

	game = param;
	if (game->is_animating == false)
		return ;
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000
		+ (current_time.tv_usec - last_time.tv_usec) / 1000;
	if (elapsed_time > 200)
	{
		change_sprites(game);
		gettimeofday(&last_time, NULL);
	}
}

void	animation(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_Q)
	{
		if (game->pistol1_img->enabled == false)
			game->pistol1_img->enabled = true;
		else if (game->pistol1_img->enabled == true)
			game->pistol1_img->enabled = false;
	}
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_LEFT_SHIFT
		&& game->pistol1_img->enabled == true)
	{
		if (!game->is_animating)
		{
			game->is_animating = true;
			game->current_sprite = 1;
			game->pistol1_img->enabled = true;
			game->pistol2_img->enabled = false;
			game->pistol3_img->enabled = false;
		}
		mlx_loop_hook(game->mlx, &animate_pistol, game);
	}
}

void	mouse_click_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_game	*game;

	(void)mods;
	game = param;
	if (action == MLX_PRESS && button == MLX_MOUSE_BUTTON_LEFT
		&& game->pistol1_img->enabled == true)
	{
		if (!game->is_animating)
		{
			game->is_animating = true;
			game->current_sprite = 1;
			game->pistol1_img->enabled = true;
			game->pistol2_img->enabled = false;
			game->pistol3_img->enabled = false;
		}
		mlx_loop_hook(game->mlx, &animate_pistol, game);
	}
}
