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

void	add_textures(char *line, t_texture *texture, int j, int z)
{
	if (!ft_strncmp(line + z, "NO", 2))
		texture->no_path = ft_strdup(line + j);
	else if (!ft_strncmp(line + z, "SO", 2))
		texture->so_path = ft_strdup(line + j);
	else if (!ft_strncmp(line + z, "EA", 2))
		texture->ea_path = ft_strdup(line + j);
	else if (!ft_strncmp(line + z, "WE", 2))
		texture->we_path = ft_strdup(line + j);
}

// en la linea 45 si es parte del color devolvemos null 
// sino segmentation fault si el color va primero

t_texture	*get_textures(char **map_array, t_texture *texture)
{
	int	i;
	int	j;
	int	z;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		handle_error(ERR_MALLOC_CODE);
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) == 2)
			return (NULL);
		z = j;
		j += 2;
		while (ft_isspace(map_array[i][j]))
			j++;
		add_textures(map_array[i], texture, j, z);
		i++;
	}
	return (texture);
}
