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

void	set_player(t_map *map)
{
	int	x;
	int	y;

	map->player_count = 0;
	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'W' || map->map[x][y] == 'E' ||
				map->map[x][y] == 'N' || map->map[x][y] == 'S')
			{
				map->player_count++;
				map->player_x = x;
				map->player_y = y;
				map->map[x][y] = '0';
			}
			if (map->map[x][y] == 'W')
				map->player_dir = WEST;
			else if (map->map[x][y] == 'E')
				map->player_dir = EAST;
			else if (map->map[x][y] == 'N')
				map->player_dir = NORTH;
			else if (map->map[x][y] == 'S')
				map->player_dir = SOUTH;
			y++;
		}
		x++;
	}
	if (map->player_count != 1)
		handle_error(ERR_PLAYER_CODE);
}

void	verify_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	int z = 0;
	while (map->map[z])
		ft_printf("%s\n", map->map[z++]);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '_')
				handle_error(ERR_EMPTY_LINE_CODE);
			else if (map->map[i][j] != '0' && map->map[i][j] != '2' &&
				map->map[i][j] != ' ' && map->map[i][j] != '1')
				handle_error(ERR_CHARS_CODE);
			j++;
		}
		i++;
	}
}

void	verify_borders(t_map *map, int x, int y)
{
	if(x >= ft_arraylen(map->map) || x < 0)
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
	else if (map->map[x][y] == '\0' ||
			map->map[x][y] == ' ')
	{
		map->map[x][y] = 'e';
		map->map_flag = 1;
		return ;
	}
	verify_borders(map, x + 1, y);
	verify_borders(map, x - 1, y);
	verify_borders(map, x, y + 1);
	verify_borders(map, x, y - 1);
	verify_borders(map, x + 1, y + 1);
	verify_borders(map, x - 1, y - 1);
	verify_borders(map, x - 1, y + 1);
	verify_borders(map, x + 1, y - 1);
}

void	verify_doors(t_map *map)
{
	int	i;
	int	j;

	i = - 1;
	while (map->map[++i])
	{
		j = - 1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '2')
			{
				if (map->map[i + 1][j] == '0' || map->map[i - 1][j] == '0')
				{
					if (map->map[i][j + 1] == '0' || map->map[i][j - 1] == '0')
						handle_error(ERR_DOOR_CODE);
				}
				else if (map->map[i][j + 1] == '0' || map->map[i][j - 1] == '0')
				{
					if (map->map[i + 1][j] == '0' || map->map[i - 1][j] == '0')
						handle_error(ERR_DOOR_CODE);

				}
			}
		}
	}
}

void check_map(t_map *map, int x, int y)
{
	verify_doors(map);
	verify_map(map);
	verify_borders(map, x, y);
}
