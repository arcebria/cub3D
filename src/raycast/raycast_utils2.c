/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:48 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 18:38:19 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	assign_textures(t_game *game, t_raycast *values)
{
	if (values->side == 0)
	{
		if (values->ray_dir_x > 0)
			values->wall_texture = game->east_texture;
		else
			values->wall_texture = game->west_texture;
	}
	if (values->side == 1)
	{
		if (values->ray_dir_y > 0)
			values->wall_texture = game->south_texture;
		else
			values->wall_texture = game->north_texture;
	}
}

void	calculate_wall_height(t_raycast *values)
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
}

void	calculate_texture_x(t_game *game, t_raycast *values)
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
}

void	render_textures(t_game *game, t_raycast *values, int x)
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
