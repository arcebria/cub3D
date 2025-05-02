/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:28 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/02 21:57:45 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3D.h"

int	check_syntax(char *str)
{
	int i;

	i = ft_strcspn(str, ".");
	if (!ft_strcmp(str + i, ".cub"))
		return (0);
	else
		ft_putstr_fd(ERR_EXTENSION, 2);
	return (1);
}

char **get_map_array(int map_fd)
{
	char	*current_line;
	char	*joined_line;
	char	*tmp_line;
	char	*tmp;
	char	**map_array;

	joined_line = NULL;
	current_line = get_next_line(map_fd);
	while (current_line)
	{
		tmp_line = joined_line;
		joined_line = ft_strjoin(tmp_line, current_line);
		free(tmp_line);
		free(current_line);
		current_line = get_next_line(map_fd);
		if (current_line && current_line[0] == '\n') //metemos en todas las lineas vacias un '_' para identificarlos en el array y gestionarlo posteriormente
		{
			tmp = current_line;
			current_line = ft_strjoin(tmp, "_\n");
			free(tmp);
		}
	}
	map_array = ft_split(joined_line, '\n');
	if (!map_array[0])
		ft_printf("Error\nMap empty\n"); //construir la funcion que gestiona los exits y los mensajes de error
	free(joined_line);
	return(map_array);
}

void	parsing(char *file_map)
{
	int		map_fd;
	char	**map_array;

	map_fd = open(file_map, O_RDONLY);//poner si map_fd < 0 que haya error
	map_array = get_map_array(map_fd);
	int i = 0;
	while (map_array[i])
	{
		ft_printf("%s\n", map_array[i]);
		i++;
	}
	ft_free_array(map_array);
}

int	main (int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd(ERR_ARGC, 2), 1);
	if (check_syntax(argv[1]))
		return (1);
	parsing(argv[1]);
	return (0);
}
