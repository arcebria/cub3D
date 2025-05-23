/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/23 22:08:02 by arcebria         ###   ########.fr       */
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

void	set_images(t_game *game)
{
	game->pistol1 = mlx_load_png("texs/pistol1.png");
	game->pistol2 = mlx_load_png("texs/pistol2.png");
	game->pistol3 = mlx_load_png("texs/pistol3.png");
	game->pistol1_img = mlx_texture_to_image(game->mlx, game->pistol1);
	game->pistol2_img = mlx_texture_to_image(game->mlx, game->pistol2);
	game->pistol3_img = mlx_texture_to_image(game->mlx, game->pistol3);
	mlx_delete_texture(game->pistol1);
	mlx_delete_texture(game->pistol2);
	mlx_delete_texture(game->pistol3);
	mlx_image_to_window(game->mlx, game->pistol1_img, SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT - 128);
}

void	render_frame(void *param)
{
	t_game	*game;

	game = param;
	set_images(game);
	raycasting(game);
}
