/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:28 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/24 18:01:07 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

//creo que hay que sacar la creacion de la imagen del juego fuera del loop
//para que no se vaya sobreescribiendo

void	set_images(t_game *game)
{
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	game->pistol1 = mlx_load_png("texs/pistol1.png");
	game->pistol2 = mlx_load_png("texs/pistol2.png");
	game->pistol3 = mlx_load_png("texs/pistol3.png");
	game->pistol2_img = mlx_texture_to_image(game->mlx, game->pistol2);
	game->pistol1_img = mlx_texture_to_image(game->mlx, game->pistol1);
	game->pistol3_img = mlx_texture_to_image(game->mlx, game->pistol3);
	mlx_delete_texture(game->pistol1);
	mlx_delete_texture(game->pistol2);
	mlx_delete_texture(game->pistol3);
	mlx_image_to_window(game->mlx, game->pistol1_img, SCREEN_WIDTH
		/ 2 - 64, SCREEN_HEIGHT - 128);
	mlx_image_to_window(game->mlx, game->pistol2_img, SCREEN_WIDTH
		/ 2 - 64, SCREEN_HEIGHT - 128);
	mlx_image_to_window(game->mlx, game->pistol3_img, SCREEN_WIDTH
		/ 2 - 64, SCREEN_HEIGHT - 128);
	game->pistol1_img->enabled = false;
	game->pistol2_img->enabled = false;
	game->pistol3_img->enabled = false;
	game->is_animating = false;
}

void	mouse_move(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT && keydata.action == MLX_PRESS)
		printf("Left mouse button pressed\n");

}

void	init_game(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	set_images(game);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_mouse_hook(game->mlx, &mouse_move, game);
	mlx_key_hook(game->mlx, &movement, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_MODE_HIDDEN);
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

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
