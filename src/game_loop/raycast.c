/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/27 19:14:24 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	render_door_texture(t_game *game, t_raycast *values, int x)
{
	int			y;
	int			screen_to_tex;
	uint8_t		*pixel;
	uint32_t	color;

	y = values->draw_start;
	while (y < values->draw_end)
	{
		screen_to_tex = y * 256 - SCREEN_HEIGHT * 128
			+ values->wall_height * 128;
		values->tex_y = ((screen_to_tex * values->tex_height)
				/ values->wall_height) / 256;
		pixel = &values->wall_texture->pixels[4 * (values->tex_width
				* values->tex_y + values->tex_x)];
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	calculate_texture_door(t_game *game, t_raycast *values, int x)
{
	if (values->side == 0)
		values->hit_in_wall = game->pos_y + values->wall_dist
			* values->ray_dir_y;
	else if (values->side == 1)
		values->hit_in_wall = game->pos_x + values->wall_dist
			* values->ray_dir_x;
	values->hit_in_wall -= floor(values->hit_in_wall);
	values->tex_height = values->wall_texture->height;
	values->tex_width = values->wall_texture->width;
	values->tex_x = (int)(values->hit_in_wall * (double)values->tex_width);
	if (values->side == 0 && values->ray_dir_x < 0)
		values->tex_x = values->tex_width - values->tex_x - 1;
	if (values->side == 1 && values->ray_dir_y > 0)
		values->tex_x = values->tex_width - values->tex_x - 1;
	render_door_texture(game, values, x);
}

void	calculate_door_height(t_game *game, t_raycast *values, int x)
{
	if (values->side == 0)
		values->wall_dist = values->side_dist_x - values->delta_dist_x;
	else if (values->side == 1)
		values->wall_dist = values->side_dist_y - values->delta_dist_y;
	values->wall_height = (int)(SCREEN_HEIGHT / values->wall_dist);
	values->draw_start = SCREEN_HEIGHT / 2 - values->wall_height / 2;
	if (values->draw_start < 0)
		values->draw_start = 0;
	values->draw_end = SCREEN_HEIGHT / 2 + values->wall_height / 2;
	if (values->draw_end >= SCREEN_HEIGHT)
		values->draw_end = SCREEN_HEIGHT - 1;
	calculate_texture_door(game, values, x);
}

void	calculate_door_hit(t_game *game, t_raycast *values, int x)
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
		if (game->map->map[values->map_y][values->map_x] == '2')
			values->hit = 1;
	}
	values->wall_texture = mlx_load_png("texs/door.png");
	calculate_door_height(game, values, x);
}

void	raycasting(t_game *game)
{
	t_raycast	values;
	int			x;

	put_color_ceiling_floor(game);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		calculate_raydir(game, &values, x);
		calculate_delta_dist(&values);
		calculate_side_dist(game, &values);
		calculate_hits(game, &values);
		calculate_door_hit(game, &values, x);
		assign_textures(game, &values);
		calculate_wall_height(&values);
		calculate_texture_x(game, &values);
		render_textures(game, &values, x);
	}
}

void	put_color_ceiling_floor(t_game *game)
{
	int			x;
	int			y;
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
	while (y < SCREEN_HEIGHT - 1)
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
