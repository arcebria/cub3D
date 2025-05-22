/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/21 22:03:26 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#include <math.h>

void	raycasting(t_game *game)
{
	t_raycast	values;
	int			x;

	x = -1;
	mlx_image_to_window(game->mlx, game->img, 0, 0);
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
			values.delta_dist_x = fabs(1 / values.ray_dir_x);
		if (values.ray_dir_y == 0)
			values.delta_dist_y = 1e30;
		else
			values.delta_dist_y = fabs(1 / values.ray_dir_y);
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
		else // values.side == 1
		{
			if (values.ray_dir_y > 0)
				values.wall_texture = game->south_texture;
			else
				values.wall_texture = game->north_texture;
		}
		//--------------------------------------------------------------
		if (values.side == 0)
			values.wall_dist = values.side_dist_x - values.delta_dist_x;
		else
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
		values.hit_in_wall = values.hit_in_wall - floor(values.hit_in_wall);
		//--------------------------------------------------------------
		values.tex_height = values.wall_texture->height;
		values.tex_width = values.wall_texture->width;
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
			pixel = &values.wall_texture->pixels[4 * (values.tex_width * values.tex_y + values.tex_x)];
			color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
			mlx_put_pixel(game->img, x, y, color);
			y++;
		}
	}
}

// void raycasting(t_game *game)
// {
//     mlx_image_to_window(game->mlx, game->img, 0, 0);
//     for (int y = 0; y < SCREEN_HEIGHT; y++)
//     	for (int x = 0; x < SCREEN_WIDTH; x++)
//         mlx_put_pixel(game->img, x, y, 0x000000FF);


//     for (int x = 0; x < SCREEN_WIDTH; x++)
//     {
//         double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
//         double rayDirX = game->dir_x + game->plane_x * cameraX;
//         double rayDirY = game->dir_y + game->plane_y * cameraX;

//         int mapX = (int)game->player_x;
//         int mapY = (int)game->player_y;

//         double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//         double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//         double sideDistX, sideDistY;

//         int stepX, stepY;
//         int hit = 0, side;

//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (game->player_x - mapX) * deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - game->player_x) * deltaDistX;
//         }
//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (game->player_y - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - game->player_y) * deltaDistY;
//         }

//         while (hit == 0)
//         {
//             if (sideDistX < sideDistY)
//             {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             }
//             else
//             {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }
//             if (game->map->map[mapY][mapX] == '1')
//                 hit = 1;
//         }

//         if (side == 0)
//         {
//             if (rayDirX < 0)
//                 game->wall_texture = game->west_texture;
//             else
//                 game->wall_texture = game->east_texture;
//         }
//         if (side == 1)
//         {
//             if (rayDirY < 0)
//                 game->wall_texture = game->north_texture;
//             else
//                 game->wall_texture = game->south_texture;
//         }

//         double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);

//         int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
//         int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
//         if (drawEnd >= SCREEN_HEIGHT)
//             drawEnd = SCREEN_HEIGHT - 1;

//         double wallX;
//         if (side == 0)
//             wallX = game->player_y + perpWallDist * rayDirY;
//         else
//             wallX = game->player_x + perpWallDist * rayDirX;
//         wallX -= floor(wallX); //floor es una funcion que redondea hacia abajo

//         int texWidth = game->wall_texture->width;
//         int texHeight = game->wall_texture->height;
//         int texX = (int)(wallX * (double)texWidth);
//         if (side == 0 && rayDirX < 0) //golpea pared oeste
//             texX = texWidth - texX - 1;
//         if (side == 1 && rayDirY > 0) //golpea pared sur
//             texX = texWidth - texX - 1;

//         for (int y = drawStart; y < drawEnd; y++)
//         {
//             int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;// se reescalan los valores para facilitar el calculo del ordenador y evitar perdida de decimales
//             int texY = ((d * texHeight) / lineHeight) / 256;
//             uint8_t *pixel = &game->wall_texture->pixels[4 * (texWidth * texY + texX)];
//             uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
//             mlx_put_pixel(game->img, x, y, color);
//         }
//     }
// }

void	render_frame(void *param)
{
	t_game	*game = (t_game *)param;
	raycasting(game);
}

void	init_game(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
