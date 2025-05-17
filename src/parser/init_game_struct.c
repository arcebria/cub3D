/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:09:17 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/17 20:42:55 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	set_dir(t_game *game)
{
	if (game->map->player_dir == NORTH)
		game->dir_y = -1.0;
	else if (game->map->player_dir == SOUTH)
		game->dir_y = 1.0;
	else if (game->map->player_dir == EAST)
		game->dir_x = 1.0;
	else if (game->map->player_dir == WEST)
		game->dir_x = -1.0;
}

t_game	*init_game_struct(t_game *game, t_map *map, t_texture *texture, t_color *color)
{
	game = malloc(sizeof(t_game));
	if (!game)
		handle_error(ERR_MALLOC_CODE);
	game->map = map;
	game->color = color;
	game->texture = texture;
	game->plane_x = FOV;
	game->plane_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->player_x = map->player_y;
	game->player_y = map->player_x;
	set_dir(game);
	return(game);
}
