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

void	count_texture(char *str, t_checker *checker)
{
	if (!ft_strncmp(str, "NO", 2))
		checker->count_no++;
	else if (!ft_strncmp(str, "SO", 2))
		checker->count_so++;
	else if (!ft_strncmp(str, "EA", 2))
		checker->count_ea++;
	else if (!ft_strncmp(str, "WE", 2))
		checker->count_we++;
	checker->count_texture++;
}

void	count_color(char *str, t_checker *checker)
{
	if (!ft_strncmp(str, "F", 1))
		checker->count_f++;
	else if (!ft_strncmp(str, "C", 1))
		checker->count_c++;
	checker->count_color++;
}

int	is_texture_color(char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		return (1);
	else if (!ft_strncmp(str, "SO", 2))
		return (1);
	else if (!ft_strncmp(str, "EA", 2))
		return (1);
	else if (!ft_strncmp(str, "WE", 2))
		return (1);
	else if (!ft_strncmp(str, "F", 1))
		return (2);
	else if (!ft_strncmp(str, "C", 1))
		return (2);
	return (0);
}

void	check_param_place(char **map_array, t_checker *checker)
{
	int	i;
	int	j;

	i = 0;
	while (map_array[i])
	{
		if (map_array[i + 1] && map_array[i][0] == ' ' && !map_array[i][1])
		{
			i++;
			continue ;
		}
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (!is_texture_color(map_array[i] + j))
			checker->map_flag = 1;
		if (checker->map_flag == 1 && is_texture_color(map_array[i] + j))
			handle_error(ERR_TEXT_COLOR_PLACE_CODE);
		i++;
	}
}

void	check_params_number(char **map_array, t_checker *checker)
{
	int	i;
	int	j;

	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) == 1)
			count_texture(map_array[i] + j, checker);
		else if (is_texture_color(map_array[i] + j) == 2)
			count_color(map_array[i] + j, checker);
		i++;
	}
	if (checker->count_texture != 4 || checker->count_color != 2
		|| checker->count_no != 1 || checker->count_so != 1
		|| checker->count_ea != 1 || checker->count_we != 1
		|| checker->count_f != 1 || checker->count_c != 1)
		handle_error(ERR_TEXT_COLOR_NUMBER_CODE);
}
