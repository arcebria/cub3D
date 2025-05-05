/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:32 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/05 19:47:16 by arcebria         ###   ########.fr       */
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

typedef struct s_texture
{
	char	*NO_path;
	char	*SO_path;
	char	*EA_path;
	char	*WE_path;
}	t_texture;

typedef struct s_color
{
	int	F_R;
	int	F_G;
	int	F_B;
	int	C_R;
	int	C_G;
	int	C_B;
}	t_color;

typedef struct s_map
{
	char	**map;
	int		player_x;
	int		player_y;
}	t_map;

void		parsing(int map_fd);
void		check_extension(char *str);
char		**get_map_array(int map_fd);
int			is_texture_color(char *str);
void		check_params_number(char **map_array, t_checker *checker);
void		check_param_place(char **map_array, t_checker *checker);
t_texture	*get_textures(char **map_array, t_texture *texture);
t_color		*get_colors(char **map_array, t_color *color);
//void get_textures(char *line);

#endif
