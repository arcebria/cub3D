/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:50:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/06 20:50:50 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	set_player_dir(t_map *map, int x, int y)
{
	if (map->map[x][y] == 'W')
		map->player_dir = WEST;
	else if (map->map[x][y] == 'E')
		map->player_dir = EAST;
	else if (map->map[x][y] == 'N')
		map->player_dir = NORTH;
	else if (map->map[x][y] == 'S')
		map->player_dir = SOUTH;
}

void	set_player(t_map *map)
{
	int	x;
	int	y;

	map->player_count = 0;
	x = -1;
	while (map->map[++x])
	{
		y = -1;
		while (map->map[x][++y])
		{
			set_player_dir(map, x, y);
			if (map->map[x][y] == 'W' || map->map[x][y] == 'E' ||
				map->map[x][y] == 'N' || map->map[x][y] == 'S')
			{
				map->player_count++;
				map->player_x = x;
				map->player_y = y;
				map->map[x][y] = '0';
			}
		}
	}
	if (map->player_count != 1)
		handle_error(ERR_PLAYER_CODE);
}
