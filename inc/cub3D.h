/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:32 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/06 18:34:53 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include "errors.h"
# include <fcntl.h>
# include <limits.h>

# define WEST 0
# define EAST 1
# define NORTH 2
# define SOUTH 3

typedef struct s_checker
{
	int	map_flag;
	int	count_texture;
	int	count_color;
	int	count_no;
	int	count_so;
	int	count_ea;
	int	count_we;
	int	count_f;
	int	count_c;
}	t_checker;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
}	t_texture;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_color
{
	int	f_r;
	int	f_g;
	int	f_b;
	int	c_r;
	int	c_g;
	int	c_b;
}	t_color;

typedef struct s_map
{
	char	**map;
	int		player_x;
	int		player_y;
	int		player_dir;
	int		map_flag;
	int		player_count;
}	t_map;

void		parsing(int map_fd);
void		check_extension(char *str);
char		**get_map_array(int map_fd);
int			is_texture_color(char *str);
void		check_params_number(char **map_array, t_checker *checker);
void		check_param_place(char **map_array, t_checker *checker);
t_texture	*get_textures(char **map_array, t_texture *texture);
t_color		*get_colors(char **map_array, t_color *color);
void		set_player(t_map *map);
void		check_map(t_map *map);
void		normalize_map(t_map *map);

#endif
