#include "../inc/cub3D.h"

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

void	parsing(int map_fd)
{
	char		**map_array;
	t_checker	*checker;

	map_array = get_map_array(map_fd);
	checker = NULL;
	checker = init_checker_struct(checker);
	check_params_number(map_array, checker); // a partir de aqui se da por supuesto que el mapa esta en el orden correcto
	check_param_place(map_array, checker);  // ahora hay que guardar los valores de los parametros en un struct y el mapa en otro
	ft_free_array(map_array);
	free(checker);
}