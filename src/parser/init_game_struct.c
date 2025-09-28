/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:09:17 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/28 14:09:29 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	set_dir(t_game *game)
{
	if (game->map->player_dir == NORTH)
	{
		game->dir_y = -1.0;
		game->plane_x = FOV;
	}
	else if (game->map->player_dir == SOUTH)
	{
		game->dir_y = 1.0;
		game->plane_x = -FOV;
	}
	else if (game->map->player_dir == EAST)
	{
		game->dir_x = 1.0;
		game->plane_y = FOV;
	}
	else if (game->map->player_dir == WEST)
	{
		game->dir_x = -1.0;
		game->plane_y = -FOV;
	}
}

void	set_textures(t_game *game)
{
	game->north_texture = mlx_load_png(game->texture->no_path);
	game->south_texture = mlx_load_png(game->texture->so_path);
	game->east_texture = mlx_load_png(game->texture->ea_path);
	game->west_texture = mlx_load_png(game->texture->we_path);
	game->door_texture = mlx_load_png("texs/door.png");
	if (!game->north_texture || !game->south_texture
		|| !game->east_texture || !game->west_texture)
		handle_error(ERR_TEXTURE_CODE);
}

t_game	*init_game_struct(t_game *game, t_map *map,
	t_texture *texture, t_color *color)
{
	game = malloc(sizeof(t_game));
	if (!game)
		handle_error(ERR_MALLOC_CODE);
	game->map = map;
	game->color = color;
	game->texture = texture;
	game->plane_x = 0.0;
	game->plane_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->pos_x = map->player_y;
	game->pos_y = map->player_x;
	set_dir(game);
	set_textures(game);
	return (game);
}
