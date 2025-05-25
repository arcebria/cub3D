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

void	put_color(t_game *game, int x, int y)
{
	int			i;
	int			j;
	uint32_t	color;

	if (game->map->map[y][x] == '1')
		color = 0xAAAAAAFF;
	else
		color = 0x222222FF;
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			mlx_put_pixel(game->minimap, x * TILE_SIZE + i,
				y * TILE_SIZE + j, color);
	}
}

void	draw_minimap(t_game *game)
{
	int			x;
	int			y;

	if (TILE_SIZE != 5)
		return ;
	y = -1;
	while (++y < ft_arraylen(game->map->map))
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map->map[y]))
			put_color(game, x, y);
	}
}

void	put_player_color(t_game *game, int center_x, int center_y)
{
	int			y;
	int			x;
	int			draw_x;
	int			draw_y;

	y = -RADIUS - 1;
	while (++y <= RADIUS)
	{
		x = -RADIUS - 1;
		while (++x <= RADIUS)
		{
			if (x * x + y * y <= RADIUS * RADIUS)
			{
				draw_x = center_x + x;
				draw_y = center_y + y;
				if (draw_x >= 0 && draw_x < game->map->map_width * TILE_SIZE
					&& draw_y >= 0 && draw_y < game->map->map_height
					* TILE_SIZE)
					mlx_put_pixel(game->minimap, draw_x, draw_y, 0x00FF00FF);
			}
		}
	}
}

void	draw_player(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = game->pos_x * TILE_SIZE;
	center_y = game->pos_y * TILE_SIZE;
	put_player_color(game, center_x, center_y);
}
