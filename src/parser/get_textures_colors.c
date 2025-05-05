#include "../../inc/cub3D.h"

void	add_textures(char *line, t_texture *texture, int j, int z)
{
	if (!ft_strncmp(line + z, "NO", 2))
			texture->NO_path = ft_strdup(line + j);
		else if (!ft_strncmp(line + z, "SO", 2))
			texture->SO_path = ft_strdup(line + j);
		else if (!ft_strncmp(line + z, "EA", 2))
			texture->EA_path = ft_strdup(line + j);
		else if (!ft_strncmp(line + z, "WE", 2))
			texture->WE_path = ft_strdup(line + j);
}

t_texture	*get_textures(char **map_array, t_texture *texture)
{
	int	i;
	int	j;
	int	z;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		handle_error(ERR_MALLOC_CODE);
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (ft_isspace(map_array[i][j]))
			j++;
		if (is_texture_color(map_array[i] + j) == 2) // si es parte del color devolvemos null si no segmentation fault si el color va primero
			return (NULL);
		z = j;
		j += 2;
		while (ft_isspace(map_array[i][j]))
			j++;
		add_textures(map_array[i], texture, j, z);
		i++;
	}
	return (texture);
}

/*
hay que repasar la norminette de add_f y add_c
tambien se pueden implementar mensajes de error especificos
para cuando faltan valores de color o hay de mas
*/
void	add_f(char **map_array, int i, int j, t_color *color)
{
	int	z;

	z = j;
	while (ft_isdigit(map_array[i][j]))
				j++;
	color->F_R = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	if (!map_array[i][j])
		handle_error(ERR_COLOR_CODE);
	z = j;
	while (ft_isdigit(map_array[i][j]))
		j++;
	color->F_G = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	if (!map_array[i][j])
		handle_error(ERR_COLOR_CODE);
	z = j;
	while (ft_isdigit(map_array[i][j]))
		j++;
	color->F_B = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]))
		j++;
	if (map_array[i][j])
		handle_error(ERR_COLOR_CODE);
}

void	add_c(char **map_array, int i, int j, t_color *color)
{
	int	z;

	z = j;
	while (ft_isdigit(map_array[i][j]))
				j++;
	color->C_R = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	if (!map_array[i][j])
		handle_error(ERR_COLOR_CODE);
	z = j;
	while (ft_isdigit(map_array[i][j]))
		j++;
	color->C_G = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]) || map_array[i][j] == ',')
		j++;
	if (!map_array[i][j])
		handle_error(ERR_COLOR_CODE);
	z = j;
	while (ft_isdigit(map_array[i][j]))
		j++;
	color->C_B = ft_atoi(ft_substr(map_array[i], z, j - z));
	while (ft_isspace(map_array[i][j]))
		j++;
	if (map_array[i][j])
		handle_error(ERR_COLOR_CODE);
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
