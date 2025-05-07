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

int	parse_color_component(char **map_array, int i, int *j)
{
	int		z;
	char	*str;
	long	color_component;

	z = *j;
	while (ft_isdigit(map_array[i][*j]))
		(*j)++;
	str = ft_substr(map_array[i], z, *j - z);
	if (!str || *str == '\0')
		handle_error(ERR_COLOR_CODE);
	color_component = ft_atoi(str);
	if (color_component < INT_MIN || color_component > INT_MAX
		|| color_component < 0 || color_component > 255)
		handle_error(ERR_COLOR_CODE);
	free(str);
	return (color_component);
}

void	process_color(char **map_array, int i, int j, t_rgb *color_value)
{
	color_value->r = parse_color_component(map_array, i, &j);
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	color_value->g = parse_color_component(map_array, i, &j);
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	color_value->b = parse_color_component(map_array, i, &j);
	while (ft_isspace(map_array[i][j]))
		j++;
	if (map_array[i][j])
		handle_error(ERR_COLOR_CODE);
}

void	add_f(char **map_array, int i, int j, t_color *color)
{
	t_rgb	floor_color;

	process_color(map_array, i, j, &floor_color);
	color->f_r = floor_color.r;
	color->f_g = floor_color.g;
	color->f_b = floor_color.b;
}

void	add_c(char **map_array, int i, int j, t_color *color)
{
	t_rgb	ceiling_color;

	process_color(map_array, i, j, &ceiling_color);
	color->c_r = ceiling_color.r;
	color->c_g = ceiling_color.g;
	color->c_b = ceiling_color.b;
}

t_color	*get_colors(char **map_array, t_color *color)
{
	int	i;
	int	j;
	int	z;

	color = malloc(sizeof(t_color));
	if (!color)
		handle_error(ERR_MALLOC_CODE);
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		z = j;
		j++;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (!ft_strncmp(map_array[i] + z, "F", 1))
			add_f(map_array, i, j, color);
		else if (!ft_strncmp(map_array[i] + z, "C", 1))
			add_c(map_array, i, j, color);
		i++;
	}
	return (color);
}
