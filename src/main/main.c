/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:28 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/21 18:45:22 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	int		map_fd;

	game = NULL;
	if (argc != 2)
		return (ft_putstr_fd(ERR_ARGC, 2), 1);
	check_extension(argv[1]);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		return (ft_putstr_fd(ERR_FILE_OPEN, 2), 1);
	game = parsing(map_fd, game);
	init_game(game);
	return (0);
}
