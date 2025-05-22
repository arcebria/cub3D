/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 18:34:40 by arcebria         ###   ########.fr       */
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

void	init_game(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
