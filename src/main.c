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

#include "../inc/cub3D.h"

int	main (int argc, char **argv)
{
	int		map_fd;

	if (argc != 2)
		return (ft_putstr_fd(ERR_ARGC, 2), 1);
	check_extension(argv[1]);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		return (ft_putstr_fd(ERR_FILE_OPEN, 2), 1);
	parsing(map_fd);
	return (0);
}
