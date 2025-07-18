/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:50:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/27 20:36:19 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	verify_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][0] == ' ' && !map->map[i][1])
			{
				while (map->map[i])
				{
					if (map->map[i][0] != ' ')
						handle_error(ERR_EMPTY_LINE_CODE);
					else if (map->map[i][0] == ' ' && !map->map[i + 1])
						break ;
					i++;
				}
			}
			else if (map->map[i][j] != '0' && map->map[i][j] != '2' &&
					map->map[i][j] != ' ' && map->map[i][j] != '1')
				handle_error(ERR_CHARS_CODE);
		}
	}
}

void	recall_function(t_map *map, int x, int y)
{
	verify_borders(map, x + 1, y);
	verify_borders(map, x - 1, y);
	verify_borders(map, x, y + 1);
	verify_borders(map, x, y - 1);
	verify_borders(map, x + 1, y + 1);
	verify_borders(map, x - 1, y - 1);
	verify_borders(map, x - 1, y + 1);
	verify_borders(map, x + 1, y - 1);
}

void	verify_borders(t_map *map, int x, int y)
{
	if (x >= ft_arraylen(map->map) || x < 0 || y < 0
		|| y >= (int)ft_strlen(map->map[0]))
	{
		map->map_flag = 1;
		return ;
	}
	if (!ft_strchr("02 ", map->map[x][y]))
		return ;
	if (map->map[x][y] == '0')
		map->map[x][y] = '.';
	else if (map->map[x][y] == '2')
		map->map[x][y] = 'p';
	else if (map->map[x][y] == '\0' || map->map[x][y] == ' ')
	{
		map->map[x][y] = 'e';
		map->map_flag = 1;
		return ;
	}
	recall_function(map, x, y);
}

void	check_map(t_map *map)
{
	set_player(map);
	verify_doors(map);
	verify_map(map);
	normalize_map(map);
	map->map_flag = 0;
	verify_borders(map, map->player_x, map->player_y);
	if (map->map_flag == 1)
		handle_error(ERR_MAP_CODE);
	map->map_width = ft_strlen(map->map[0]);
	map->map_height = ft_arraylen(map->map);
}
