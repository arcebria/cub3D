/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:44:50 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/21 17:42:44 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_structs(t_texture *texture, t_color *color, t_map *map)
{
	if (texture)
	{
		if (texture->no_path)
			free(texture->no_path);
		if (texture->so_path)
			free(texture->so_path);
		if (texture->ea_path)
			free(texture->ea_path);
		if (texture->we_path)
			free(texture->we_path);
		free (texture);
	}
	if (color)
		free(color);
	if (map)
	{
		if (map->map)
			ft_free_array(map->map);
		free(map);
	}
}

void	handle_error(int error_code)
{
	if (error_code == ERR_EXTENSION_CODE)
		ft_putstr_fd(ERR_EXTENSION, 2);
	else if (error_code == ERR_EMPTY_MAP_CODE)
		ft_putstr_fd(ERR_EMPTY_MAP, 2);
	else if (error_code == ERR_MALLOC_CODE)
		ft_putstr_fd(ERR_MALLOC, 2);
	else if (error_code == ERR_TEXT_COLOR_PLACE_CODE)
		ft_putstr_fd(ERR_TEXT_COLOR_PLACE, 2);
	else if (error_code == ERR_TEXT_COLOR_NUMBER_CODE)
		ft_putstr_fd(ERR_TEXT_COLOR_NUMBER, 2);
	else if (error_code == ERR_COLOR_CODE)
		ft_putstr_fd(ERR_COLOR, 2);
	else if (error_code == ERR_MAP_CODE)
		ft_putstr_fd(ERR_MAP, 2);
	else if (error_code == ERR_PLAYER_CODE)
		ft_putstr_fd(ERR_PLAYER, 2);
	else if (error_code == ERR_CHARS_CODE)
		ft_putstr_fd(ERR_CHARS, 2);
	else if (error_code == ERR_EMPTY_LINE_CODE)
		ft_putstr_fd(ERR_EMPTY_LINE, 2);
	else if (error_code == ERR_DOOR_CODE)
		ft_putstr_fd(ERR_DOOR, 2);
	else if (error_code == ERR_TEXTURE_CODE)
		ft_putstr_fd(ERR_TEXTURE, 2);
	exit(error_code);
}
