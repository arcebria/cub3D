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

void	move_camera(t_game *g, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT)
	{
		g->old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(ROT_SPEED) - g->dir_y * sin(ROT_SPEED);
		g->dir_y = g->old_dir_x * sin(ROT_SPEED) + g->dir_y * cos(ROT_SPEED);
		g->old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(ROT_SPEED) - g->plane_y * sin(ROT_SPEED);
		g->plane_y = g->old_plane_x * sin(ROT_SPEED)
			+ g->plane_y * cos(ROT_SPEED);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		g->old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(-ROT_SPEED) - g->dir_y * sin(-ROT_SPEED);
		g->dir_y = g->old_dir_x * sin(-ROT_SPEED)
			+ g->dir_y * cos(-ROT_SPEED);
		g->old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(-ROT_SPEED)
			- g->plane_y * sin(-ROT_SPEED);
		g->plane_y = g->old_plane_x * sin(-ROT_SPEED)
			+ g->plane_y * cos(-ROT_SPEED);
	}
}

#include <sys/time.h>

void	animate_pistol(void *param)
{
	t_game				*game;
	game = param;
    static struct timeval	last_time;
    struct timeval			current_time;
    long					elapsed_time;

	if (game->is_animating == false)
		return ;
    gettimeofday(&current_time, NULL);
    elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 +
                   (current_time.tv_usec - last_time.tv_usec) / 1000;

    if (elapsed_time > 200) // Cambiar sprite cada 100 ms
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
            game->is_animating = 0; // Finalizar la animación
        }
        gettimeofday(&last_time, NULL); // Actualizar el tiempo del último cambio
    }
}

void	animation(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_SPACE)
	{
		if (game->pistol1_img->enabled == false)
			game->pistol1_img->enabled = true;
		else if (game->pistol1_img->enabled == true)
			game->pistol1_img->enabled = false;
	}
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_LEFT_SHIFT && game->pistol1_img->enabled == true)
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

void	movement(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		move_forward_back(game, keydata);
		move_right_left(game, keydata);
		move_camera(game, keydata);
		animation(game, keydata);
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(game->mlx);
			exit(0);
		}
	}
}
