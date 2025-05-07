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

int	get_max_len(t_map *map)
{
	int	i;
	int	max_len;
	int	len;

	max_len = 0;
	i = -1;
	while (map->map[++i])
	{
		len = ft_strlen(map->map[i]);
		if (len > max_len)
			max_len = len;
	}
	return (max_len);
}

void	normalize_map(t_map *map)
{
	int		i;
	int		max_len;
	int		len;
	char	*new_row;

	max_len = get_max_len(map);
	i = -1;
	while (map->map[++i])
	{
		len = ft_strlen(map->map[i]);
		if (len < max_len)
		{
			new_row = malloc(sizeof(char) * max_len + 1);
			if (!new_row)
				handle_error(ERR_MALLOC_CODE);
			ft_memcpy(new_row, map->map[i], len);
			ft_memset(new_row + len, ' ', max_len - len);
			new_row[max_len] = '\0';
			free(map->map[i]);
			map->map[i] = new_row;
		}
	}
}
