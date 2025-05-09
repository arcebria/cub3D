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

char	*join_lines(char *joined_line, char *current_line)
{
	char	*tmp_line;

	tmp_line = joined_line;
	joined_line = ft_strjoin(tmp_line, current_line);
	free(tmp_line);
	free(current_line);
	return (joined_line);
}

// metemos en todas las lineas vacias un espacio ' ' para identificarlos 
// en el array y gestionarlo posteriormente

char	**get_map_array(int map_fd)
{
	char	*current_line;
	char	*joined_line;
	char	*tmp;
	char	**map_array;

	joined_line = NULL;
	current_line = get_next_line(map_fd);
	while (current_line)
	{
		joined_line = join_lines(joined_line, current_line);
		current_line = get_next_line(map_fd);
		if (current_line && current_line[0] == '\n')
		{
			tmp = current_line;
			current_line = ft_strjoin(tmp, " \n");
			free(tmp);
		}
	}
	map_array = ft_split(joined_line, '\n');
	if (!map_array || !map_array[0])
		handle_error(ERR_EMPTY_MAP_CODE);
	free(joined_line);
	return (map_array);
}
