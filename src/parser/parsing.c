/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:54 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/06 20:51:16 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	check_extension(char *str)
{
	int i;

	i = ft_strcspn(str, ".");
	if (!ft_strcmp(str + i, ".cub"))
		return ;
	else
		handle_error(ERR_EXTENSION_CODE);
}

t_checker	*init_checker_struct(t_checker *checker)
{
	checker = malloc(sizeof(t_checker));
	if (!checker)
		handle_error(ERR_MALLOC_CODE);
	checker->map_flag = 0;
	checker->count_texture = 0;
	checker->count_color = 0;
	checker->count_NO = 0;
	checker->count_SO = 0;
	checker->count_EA = 0;
	checker->count_WE = 0;
	checker->count_F = 0;
	checker->count_C = 0;
	return (checker);
}

int	advance_to_map(char **map_array, int i)
{
	int	j;

	i = 0;
	j = 0;
	while (map_array[i])
	{
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) || map_array[i][0] == '_')
			i++;
		else
			break;
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

void	parsing(int map_fd)
{
	char		**map_array;
	t_checker	*checker;
	t_texture	*texture;
	t_color		*color;
	t_map		*map;

	map_array = get_map_array(map_fd);
	checker = NULL;
	checker = init_checker_struct(checker);
	check_params_number(map_array, checker); // a partir de aqui se da por supuesto que el mapa esta en el orden correcto
	check_param_place(map_array, checker);  // ahora hay que guardar los valores de los parametros en un struct y el mapa en otro
	texture = NULL;
	texture = get_textures(map_array, texture);
	color = NULL;
	color = get_colors(map_array, color);
	map = NULL;
	map = copy_map(map_array, map);
	set_player(map);
	map->map_flag = 0;
	check_map(map, map->player_x, map->player_y);
	if (map->map_flag == 1)
		handle_error(ERR_MAP_CODE);
	ft_free_array(map->map);
	free(map);
	free(checker);
	free(color);
	free(texture); // pasa algo con este free
}
