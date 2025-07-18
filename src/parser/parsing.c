/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:54 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 18:32:38 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	check_extension(char *str)
{
	int	i;

	i = ft_strcspn(str, ".");
	if (!ft_strcmp(str + i, ".cub"))
		return ;
	else
		handle_error(ERR_EXTENSION_CODE);
}

void	init_checker(char **map_array)
{
	t_checker	checker;

	checker.map_flag = 0;
	checker.count_texture = 0;
	checker.count_color = 0;
	checker.count_no = 0;
	checker.count_so = 0;
	checker.count_ea = 0;
	checker.count_we = 0;
	checker.count_f = 0;
	checker.count_c = 0;
	check_params_number(map_array, &checker);
	check_param_place(map_array, &checker);
}

int	advance_to_map(char **map_array, int i)
{
	int	j;

	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) || (map_array[i][0] == ' '
			&& map_array[i][1] == '\0'))
			i++;
		else
			break ;
	}
	return (i);
}

t_map	*copy_map(char **map_array, t_map *map)
{
	int	i;
	int	j;

	map = malloc(sizeof(t_map));
	if (!map)
		handle_error(ERR_MALLOC_CODE);
	i = advance_to_map(map_array, 0);
	j = 0;
	map->map = malloc(sizeof(char *) * (ft_arraylen(map_array + i) + 1));
	while (map_array[i])
	{
		map->map[j] = ft_strdup(map_array[i]);
		i++;
		j++;
	}
	map->map[j] = NULL;
	if (!map->map[0])
		handle_error(ERR_EMPTY_MAP_CODE);
	ft_free_array(map_array);
	return (map);
}

//A partir de check_params_number se da por supuesto
// que el mapa esta en el orden correcto

t_game	*parsing(int map_fd, t_game *game)
{
	char		**map_array;
	t_texture	*texture;
	t_color		*color;
	t_map		*map;

	texture = NULL;
	color = NULL;
	map = NULL;
	map_array = get_map_array(map_fd);
	init_checker(map_array);
	texture = get_textures(map_array, texture);
	color = get_colors(map_array, color);
	map = copy_map(map_array, map);
	check_map(map);
	game = init_game_struct(game, map, texture, color);
	return (game);
}
