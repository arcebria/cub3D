/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:32 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/02 20:07:23 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../libft/ft_printf.h"
#include "errors.h"
#include "fcntl.h"

typedef struct s_checker
{
	int	map_flag;
	int	count_texture;
	int	count_color;
	int	count_NO;
	int	count_SO;
	int	count_EA;
	int	count_WE;
	int	count_F;
	int	count_C;
}	t_checker;

void	parsing(int map_fd);
void	check_extension(char *str);
char	**get_map_array(int map_fd);
void	check_params_number(char **map_array, t_checker *checker);
void	check_param_place(char **map_array, t_checker *checker);

#endif
