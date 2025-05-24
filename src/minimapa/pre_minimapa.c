#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 7
#define TILE_SIZE 64

typedef struct s_game
{
    mlx_t *mlx;
    mlx_image_t *img;
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    char map[MAP_HEIGHT][MAP_WIDTH];
    int show_debug;
}   t_game;

int	is_walkable(t_game *game, double x, double y)
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return (0);
	if (game->map[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

void clear_image(mlx_image_t *img, uint32_t color)
{
    for (uint32_t y = 0; y < img->height; y++)
    {
        for (uint32_t x = 0; x < img->width; x++)
            mlx_put_pixel(img, x, y, color);
    }
}

void draw_map(t_game *game)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            uint32_t color = (game->map[y][x] == '1') ? 0xAAAAAAFF : 0x222222FF;
            // Dibujar tile
            for (int i = 0; i < TILE_SIZE; i++)
            {
                for (int j = 0; j < TILE_SIZE; j++)
                {
                    mlx_put_pixel(game->img, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
                }
            }
            // Dibujar borde blanco (o gris claro)
            for (int i = 0; i < TILE_SIZE; i++)
            {
                mlx_put_pixel(game->img, x * TILE_SIZE + i, y * TILE_SIZE, 0xFFFFFFFF); // arriba
                mlx_put_pixel(game->img, x * TILE_SIZE + i, y * TILE_SIZE + TILE_SIZE - 1, 0xFFFFFFFF); // abajo
            }
            for (int j = 0; j < TILE_SIZE; j++)
            {
                mlx_put_pixel(game->img, x * TILE_SIZE, y * TILE_SIZE + j, 0xFFFFFFFF); // izquierda
                mlx_put_pixel(game->img, x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE + j, 0xFFFFFFFF); // derecha
            }
        }
    }
}

void draw_player(t_game *game)
{
    int center_x = game->pos_x * TILE_SIZE;
    int center_y = game->pos_y * TILE_SIZE;
    int radius = 6;

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int draw_x = center_x + x;
                int draw_y = center_y + y;
                if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0 && draw_y < SCREEN_HEIGHT)
                    mlx_put_pixel(game->img, draw_x, draw_y, 0x00FF00FF);
            }
        }
    }
}

void draw_ray(t_game *game, double ray_dir_x, double ray_dir_y, int ray_id)
{
    int mapX = (int)game->pos_x;
    int mapY = (int)game->pos_y;

    (void)ray_id; // Para evitar warnings de variable no utilizada
    double sideDistX;
    double sideDistY;

    double deltaDistX = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    double deltaDistY = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

    int stepX = (ray_dir_x < 0) ? -1 : 1;
    int stepY = (ray_dir_y < 0) ? -1 : 1;

    if (ray_dir_x < 0)
        sideDistX = (game->pos_x - mapX) * deltaDistX;
    else
        sideDistX = (mapX + 1.0 - game->pos_x) * deltaDistX;
    if (ray_dir_y < 0)
        sideDistY = (game->pos_y - mapY) * deltaDistY;
    else
        sideDistY = (mapY + 1.0 - game->pos_y) * deltaDistY;

    int hit = 0;
    int side; // 0: vertical, 1: horizontal

    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (!is_walkable(game, mapX, mapY))
            break;
        if (game->map[mapY][mapX] == '1')
            hit = 1;
    }

    double hitX, hitY;
    if (side == 0)
    {
        double distance = sideDistX - deltaDistX;
        hitX = game->pos_x + distance * ray_dir_x;
        hitY = game->pos_y + distance * ray_dir_y;
    }
    else
    {
        double distance = sideDistY - deltaDistY;
        hitX = game->pos_x + distance * ray_dir_x;
        hitY = game->pos_y + distance * ray_dir_y;
    }

    int px0 = game->pos_x * TILE_SIZE;
    int py0 = game->pos_y * TILE_SIZE;
    int px1 = hitX * TILE_SIZE;
    int py1 = hitY * TILE_SIZE;

    int dx = abs(px1 - px0);
    int dy = abs(py1 - py0);
    int sx = (px0 < px1) ? 1 : -1;
    int sy = (py0 < py1) ? 1 : -1;
    int err = dx - dy;

    while (px0 != px1 || py0 != py1)
    {
        if (px0 >= 0 && px0 < SCREEN_WIDTH && py0 >= 0 && py0 < SCREEN_HEIGHT)
            mlx_put_pixel(game->img, px0, py0, 0xFF0000FF);

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            px0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            py0 += sy;
        }
    }

    if (game->show_debug)
    {
        // Removed debug print statements
    }
}

void handle_input(t_game *game)
{
    double move_speed = 0.05;
    double rot_speed = 0.05;

    double new_pos_x = game->pos_x;
    double new_pos_y = game->pos_y;

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        new_pos_x += game->dir_x * move_speed;
        new_pos_y += game->dir_y * move_speed;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        new_pos_x -= game->dir_x * move_speed;
        new_pos_y -= game->dir_y * move_speed;
    }

    if (is_walkable(game, new_pos_x, game->pos_y))
        game->pos_x = new_pos_x;
    if (is_walkable(game, game->pos_x, new_pos_y))
        game->pos_y = new_pos_y;

    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        double old_dir_x = game->dir_x;
        game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
        game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        double old_dir_x = game->dir_x;
        game->dir_x = game->dir_x * cos(-rot_speed) - game->dir_y * sin(-rot_speed);
        game->dir_y = old_dir_x * sin(-rot_speed) + game->dir_y * cos(-rot_speed);
    }

    game->show_debug = mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT);
}

void render_frame(void *param)
{
    t_game *game = (t_game *)param;
    handle_input(game);
    clear_image(game->img, 0x000000FF);
    draw_map(game);
    draw_player(game);

    // Draw 3 rays with small angle offset
    double fov = 0.1; // small for clarity
    for (int i = -1; i <= 1; i++)
    {
        double angle_offset = i * fov;
        double ray_dir_x = game->dir_x * cos(angle_offset) - game->dir_y * sin(angle_offset);
        double ray_dir_y = game->dir_x * sin(angle_offset) + game->dir_y * cos(angle_offset);
        draw_ray(game, ray_dir_x, ray_dir_y, i + 1); // Para que los IDs sean 0, 1, 2
    }
}

int main(void)
{
    t_game game = {
        .pos_x = 3.2,
        .pos_y = 5.5,
        .dir_x = 0,
        .dir_y = 1,
        .map = {
            "1111111111",
            "1001000001",
            "1000000001",
            "1001000001",
            "1000000001",
            "1000000001",
            "1111111111"
        },
        .show_debug = 0
    };
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D MINI", true);
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);

    mlx_image_to_window(game.mlx, game.img, 0, 0);

    mlx_loop_hook(game.mlx, render_frame, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    return (0);
}

