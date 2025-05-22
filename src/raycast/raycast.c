/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 19:40:04 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	raycasting(t_game *game)
{
	t_raycast	values;
	int			x;

	mlx_image_to_window(game->mlx, game->img, 0, 0);
	put_color_ceiling_floor(game);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		calculate_raydir(game, &values, x);
		calculate_delta_dist(&values);
		calculate_side_dist(game, &values);
		calculate_hits(game, &values);
		assign_textures(game, &values);
		calculate_wall_height(&values);
		calculate_texture_x(game, &values);
		render_textures(game, &values, x);
	}
}

void	render_frame(void *param)
{
	t_game	*game;

	game = param;
	raycasting(game);
}
