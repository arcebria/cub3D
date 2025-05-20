/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/19 20:57:04 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	raycasting(t_game *game)
{
	int		i;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		//camera x convierte cada pixel(i) dentro de un rango entre -1 a 1
		camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
		//la direccion del rayo es la suma de la direccion de x o y + la desviacion del plano y la camara
		//cuanto mayor sea el plano de x mayor sera la desviacion de los rayos situados en los extremos
		// y mayor sera el ancho del cono de vision
		ray_dir_x = game->dir_x + game->plane_x * camera_x;
		ray_dir_y = game->dir_y + game->plane_y * camera_x;
		map_x = (int)game->player_x;
		map_y = (int)game->player_y;
		//delta_dis es la distancia que debe recorrer el rayo para atravesar una cuadricula (ya sea en el eje x o y)
		//cuanto menor sea la direccion del rayo en ese eje mas distancia debera recorrer hasta la siguiente cuadricula
		//por eso se calcula dividiendolo a 1 --> hay 1u entre cada linea de los ejes, para recorrer esa unidad, cuanto mas perpendicular es un rayo respecto a su eje
		//es decir, cuanto menor sea su ray_dir en ese eje, mas distancia recorrera hasta cruzar una nueva linea de su eje (mayor delta_dis)
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = ft_fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = ft_fabs(1 / ray_dir_y);
		//aqui se divide por ray_dir por la misma razon que antes, dividimos la distancia real dentro de las cuadriculas entre el jugador y la siguiente linea
		//y luego dividimos por la inclinacion del rayo para medir la distancia del rayo desde la posicion del rayo hasta la siguiente linea del eje
		//aqui en el codigo de chatgpt se multiplicaba por delta_dis, es lo mismo pero creo que asi es mas claro
		if (ray_dir_x < 0)
		{
			side_dist_x = (game->player_x - map_x) / ray_dir_x;
			step_x = -1;
		}
		else
		{
			side_dist_x = (map_x + 1 - game->player_x) / ray_dir_x;
			step_x = 1;
		}
		if (ray_dir_y < 0)
		{
			side_dist_y = (game->player_y - map_y) / ray_dir_y;
			step_y = -1;
		}
		else
		{
			side_dist_y = (map_y + 1 - game->player_y) / ray_dir_y;
			step_y = 1;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map->map[map_x][map_y] == '1')
				hit = 1;
		}
	}
}

void	init_game(t_game *game)
{
	raycasting(game);
}
