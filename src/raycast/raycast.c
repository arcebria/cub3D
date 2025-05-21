/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/21 18:18:28 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

//me parece que esto no hace falta, simplemente cuandp haya que cambiar una valor fuera de la
//funcion principal se le pasa la direccion de memoria del struct y se cambia el valor alli
//no hace falta inicializar ninguna variable porque ya se inicializan en las mismas funciones
/*void	init_raycast_struct(t_raycast *values)
{
	values->camera_x = 0;
	values->ray_dir_x = 0;
	values->ray_dir_y = 0;
	values->map_x = 0;
	values->map_y = 0;
	values->delta_dist_x = 0;
	values->delta_dist_y = 0;
	values->side_dist_x = 0;
	values->side_dist_y = 0;
	values->step_x = 0;
	values->step_y = 0;
	values->hit = 0;
	values->side = 0;
	values->wall_dist = 0;
	values->tex_width = 0;
	values->tex_height = 0;
	values->tex_x = 0;
	values->tex_y = 0;
}*/

void	raycasting(t_game *game)
{
	t_raycast	values;
	int			x;

	//init_raycast_struct(&values);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		//camera x convierte cada pixel(i) dentro de un rango entre -1 a 1
		values.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		//la direccion del rayo es la suma de la direccion de x o y + la desviacion del plano y la camara
		//cuanto mayor sea el plano de x mayor sera la desviacion de los rayos situados en los extremos
		// y mayor sera el ancho del cono de vision
		values.ray_dir_x = game->dir_x + game->plane_x * values.camera_x;
		values.ray_dir_y = game->dir_y + game->plane_y * values.camera_x;
		values.map_x = (int)game->player_x;
		values.map_y = (int)game->player_y;
		//delta_dis es la distancia que debe recorrer el rayo para atravesar una cuadricula (ya sea en el eje x o y)
		//cuanto menor sea la direccion del rayo en ese eje mas distancia debera recorrer hasta la siguiente cuadricula
		//por eso se calcula dividiendolo a 1 --> hay 1u entre cada linea de los ejes, para recorrer esa unidad, cuanto mas perpendicular es un rayo respecto a su eje
		//es decir, cuanto menor sea su ray_dir en ese eje, mas distancia recorrera hasta cruzar una nueva linea de su eje (mayor delta_dis)
		if (values.ray_dir_x == 0)
			values.delta_dist_x = 1e30;
		else
			values.delta_dist_x = ft_fabs(1 / values.ray_dir_x);
		if (values.ray_dir_y == 0)
			values.delta_dist_y = 1e30;
		else
			values.delta_dist_y = ft_fabs(1 / values.ray_dir_y);
		//-------------------------------------------------------------
		//aqui se divide por ray_dir por la misma razon que antes, dividimos la distancia real dentro de las cuadriculas entre el jugador y la siguiente linea
		//y luego dividimos por la inclinacion del rayo para medir la distancia del rayo desde la posicion del rayo hasta la siguiente linea del eje
		//aqui en el codigo de chatgpt se multiplicaba por delta_dis, es lo mismo pero creo que asi es mas claro
		if (values.ray_dir_x < 0)
		{
			values.side_dist_x = (game->player_x - values.map_x) / values.ray_dir_x;
			values.step_x = -1;
		}
		else
		{
			values.side_dist_x = (values.map_x + 1 - game->player_x) / values.ray_dir_x;
			values.step_x = 1;
		}
		if (values.ray_dir_y < 0)
		{
			values.side_dist_y = (game->player_y - values.map_y) / values.ray_dir_y;
			values.step_y = -1;
		}
		else
		{
			values.side_dist_y = (values.map_y + 1 - game->player_y) / values.ray_dir_y;
			values.step_y = 1;
		}
		//-------------------------------------------------------------
		values.hit = 0;
		while (values.hit == 0)
		{
			if (values.side_dist_x < values.side_dist_y)
			{
				values.side_dist_x += values.delta_dist_x;
				values.map_x += values.step_x;
				values.side = 0;
			}
			else
			{
				values.side_dist_y += values.delta_dist_y;
				values.map_y += values.step_y;
				values.side = 1;
			}
			if (game->map->map[values.map_x][values.map_y] == '1')
				values.hit = 1;
		}
		//-------------------------------------------------------------
		if (values.side == 0)
		{
			if (values.ray_dir_x > 0)
				values.wall_texture = game->east_texture;
			else
				values.wall_texture = game->west_texture;
		}
		if (values.side == 1)
		{
			if (values.ray_dir_y > 0)
				values.wall_texture = game->south_texture;
			else
				values.wall_texture = game->north_texture;
		}
		//--------------------------------------------------------------
		if (values.hit == 0)
			values.wall_dist = values.side_dist_x  - values.delta_dist_x;
		else if (values.hit == 1)
			values.wall_dist = values.side_dist_y - values.delta_dist_y;
		values.line_height = (int)(SCREEN_HEIGHT / values.wall_dist);
		values.draw_start = SCREEN_HEIGHT / 2 - values.line_height / 2;
		if (values.draw_start < 0)
			values.draw_start = 0;
		values.draw_end = SCREEN_HEIGHT / 2 + values.line_height / 2;
		if (values.draw_end >= SCREEN_HEIGHT)
			values.draw_end = SCREEN_HEIGHT - 1;
		if (values.side == 0)
			values.hit_in_wall = game->player_y + values.wall_dist * values.ray_dir_y;
		else if (values.side == 1)
			values.hit_in_wall = game->player_x + values.wall_dist * values.ray_dir_x;
		values.hit_in_wall = values.hit_in_wall - ft_floor(values.hit_in_wall);
		//--------------------------------------------------------------
		values.tex_height = game->wall_texture->height;
		values.tex_width = game->wall_texture->width;
		values.tex_x = (int)(values.hit_in_wall * (double)values.tex_width);
		if (values.side == 0 && values.ray_dir_x < 0)
			values.tex_x = values.tex_width - values.tex_x - 1;
		if (values.side == 1 && values.ray_dir_y > 0)
			values.tex_x = values.tex_width - values.tex_x - 1;
		// --------------------------------------------------------------
		int	y = values.draw_start;
		int	screen_to_tex;
		uint8_t	*pixel;
		uint32_t	color;
		while (y < values.draw_end)
		{
			screen_to_tex = y * 256 - SCREEN_HEIGHT * 128 + values.line_height * 128;
			values.tex_y = ((screen_to_tex * values.tex_height) / values.line_height) / 256;
			pixel = &game->wall_texture->pixels[4 * (values.tex_width * values.tex_y + values.tex_x)];
			color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
			mlx_put_pixel(game->img, x, y, color);
			y++;
		}
	}
}

void	init_game(t_game *game)
{
	raycasting(game);
}
