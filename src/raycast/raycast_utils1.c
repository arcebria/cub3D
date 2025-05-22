/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 18:54:53 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	put_color_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = (game->color->c_r << 24) | (game->color->c_g << 16)
		| (game->color->c_b << 8) | 255;
	floor_color = (game->color->f_r << 24) | (game->color->f_g << 16)
		| (game->color->f_b << 8) | 255;
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			mlx_put_pixel(game->img, x, y, ceiling_color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			mlx_put_pixel(game->img, x, y, floor_color);
		y++;
	}
}

void	calculate_raydir(t_game *game, t_raycast *values, int x)
{
	values->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	values->ray_dir_x = game->dir_x + game->plane_x * values->camera_x;
	values->ray_dir_y = game->dir_y + game->plane_y * values->camera_x;
	values->map_x = (int)game->pos_x;
	values->map_y = (int)game->pos_y;
}

void	calculate_delta_dist(t_raycast *values)
{
	if (values->ray_dir_x == 0)
		values->delta_dist_x = 1e30;
	else
		values->delta_dist_x = fabs(1 / values->ray_dir_x);
	if (values->ray_dir_y == 0)
		values->delta_dist_y = 1e30;
	else
		values->delta_dist_y = fabs(1 / values->ray_dir_y);
}

void	calculate_side_dist(t_game *game, t_raycast *values)
{
	if (values->ray_dir_x < 0)
	{
		values->side_dist_x = (game->pos_x - values->map_x)
			* values->delta_dist_x;
		values->step_x = -1;
	}
	else
	{
		values->side_dist_x = (values->map_x + 1 - game->pos_x)
			* values->delta_dist_x;
		values->step_x = 1;
	}
	if (values->ray_dir_y < 0)
	{
		values->side_dist_y = (game->pos_y - values->map_y)
			* values->delta_dist_y;
		values->step_y = -1;
	}
	else
	{
		values->side_dist_y = (values->map_y + 1 - game->pos_y)
			* values->delta_dist_y;
		values->step_y = 1;
	}
}

void	calculate_hits(t_game *game, t_raycast *values)
{
	values->hit = 0;
	while (values->hit == 0)
	{
		if (values->side_dist_x < values->side_dist_y)
		{
			values->side_dist_x += values->delta_dist_x;
			values->map_x += values->step_x;
			values->side = 0;
		}
		else
		{
			values->side_dist_y += values->delta_dist_y;
			values->map_y += values->step_y;
			values->side = 1;
		}
		if (game->map->map[values->map_y][values->map_x] == '1')
			values->hit = 1;
	}
}
