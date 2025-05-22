/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:32 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/22 19:49:17 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include "errors.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define FOV 0.6
# define MOVE_SPEED 0.1

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
	int		map_width;
	int		map_height;
}	t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	double			dir_x;
	double			dir_y;
	double			pos_x;
	double			pos_y;
	double			plane_x;
	double			plane_y;
	t_color			*color;
	t_texture		*texture;
	t_map			*map;
}	t_game;

typedef struct s_raycast
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			wall_dist;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	double			hit_in_wall;
	int				tex_width;
	int				tex_height;
	int				tex_x;
	int				tex_y;
	mlx_texture_t	*wall_texture;
}	t_raycast;

//parsing
t_game		*parsing(int map_fd, t_game *game);
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
void		verify_borders(t_map *map, int x, int y);

//init_game
void	render_frame(void *param);

// Raycasting
t_game		*init_game_struct(t_game *game, t_map *map,
				t_texture *texture, t_color *color);
void		init_game(t_game *game);
void		put_color_ceiling_floor(t_game *game);
void		calculate_raydir(t_game *game, t_raycast *values, int x);
void		calculate_delta_dist(t_raycast *values);
void		calculate_side_dist(t_game *game, t_raycast *values);
void		calculate_hits(t_game *game, t_raycast *values);
void		assign_textures(t_game *game, t_raycast *values);
void		calculate_wall_height(t_raycast *values);
void		calculate_texture_x(t_game *game, t_raycast *values);
void		render_textures(t_game *game, t_raycast *values, int x);

//movement
void	movement(mlx_key_data_t keydata, void *param);

//frees
void		free_structs(t_texture *texture, t_color *color, t_map *map);

#endif
