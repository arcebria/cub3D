/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:36:01 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/27 20:36:25 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	check_borders(t_map *map, int i, int j)
{
	if ((i - 1 < 0) || (i + 1 > ft_arraylen(map->map)) || (j - 1 < 0)
		|| (j + 1 > (int)ft_strlen(map->map[i])))
		handle_error(ERR_DOOR_CODE);
}

void	verify_doors(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '2')
			{
				check_borders(map, i, j);
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
