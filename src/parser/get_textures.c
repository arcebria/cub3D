/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:50:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/13 17:39:05 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

t_texture	*add_textures(char *line, t_texture *texture, int j, int z)
{
	int	x;

	x = 0;
	while (!ft_isspace(line[j + x]) && line[j + x])
		x++;
	if (!ft_strncmp(line + z, "NO", 2))
		texture->no_path = ft_strndup(line + j, x);
	else if (!ft_strncmp(line + z, "SO", 2))
		texture->so_path = ft_strndup(line + j, x);
	else if (!ft_strncmp(line + z, "EA", 2))
		texture->ea_path = ft_strndup(line + j, x);
	else if (!ft_strncmp(line + z, "WE", 2))
		texture->we_path = ft_strndup(line + j, x);
	return (texture);
}

// en la linea 45 si es parte del color devolvemos null
// sino segmentation fault si el color va primero

t_texture	*init_texture(t_texture *texture)
{
	texture = malloc(sizeof(t_texture));
	if (!texture)
		handle_error(ERR_MALLOC_CODE);
	texture->ea_path = NULL;
	texture->no_path = NULL;
	texture->we_path = NULL;
	texture->so_path = NULL;
	return (texture);
}

t_texture	*get_textures(char **map_array, t_texture *texture)
{
	int	i;
	int	j;
	int	z;

	texture = init_texture(texture);
	i = -1;
	while (map_array[++i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) == 2
			|| (map_array[i][0] == ' ' && !map_array[i][1]))
			continue ;
		else if (!is_texture_color(map_array[i] + j))
			break ;
		z = j;
		j += 2;
		while (ft_isspace(map_array[i][j]))
			j++;
		texture = add_textures(map_array[i], texture, j, z);
	}
	return (texture);
}
