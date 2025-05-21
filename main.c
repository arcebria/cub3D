#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.1
#define COS90 0
#define SIN90 1
#define FOV 0.6

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "1111",
    "1001",
    "1001",
    "1001",
    "1111"
};

typedef struct s_game
{
    mlx_t         *mlx;
    mlx_image_t   *img;
    mlx_texture_t *wall_texture;
    double        posX;
    double        posY;
    double        dirX;
    double        dirY;
    double        planeX;
    double        planeY;
}   t_game;

// Comprueba si una posición es transitable (no pared)
int is_walkable(double x, double y)
{
    if (map[(int)y][(int)x] != '1')
        return (1);
    return (0);
}


// Raycasting con textura
void raycasting(t_game *game)
{
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    	for (int x = 0; x < SCREEN_WIDTH; x++)
        mlx_put_pixel(game->img, x, y, 0x000000FF);


    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double sideDistX, sideDistY;

        int stepX, stepY;
        int hit = 0, side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        while (hit == 0)
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
            if (map[mapY][mapX] == '1')
                hit = 1;
        }

        double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        double wallX;
        if (side == 0)
            wallX = game->posY + perpWallDist * rayDirY;
        else
            wallX = game->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX); //floor es una funcion que redondea hacia abajo

        int texWidth = game->wall_texture->width;
        int texHeight = game->wall_texture->height;
        int texX = (int)(wallX * (double)texWidth);
        if (side == 0 && rayDirX < 0) //golpea pared oeste
            texX = texWidth - texX - 1;
        if (side == 1 && rayDirY > 0) //golpea pared sur
            texX = texWidth - texX - 1;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;// se reescalan los valores para facilitar el calculo del ordenador y evitar perdida de decimales
            int texY = ((d * texHeight) / lineHeight) / 256;
            uint8_t *pixel = &game->wall_texture->pixels[4 * (texWidth * texY + texX)];
            uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
            mlx_put_pixel(game->img, x, y, color);
        }
    }
}

void render_frame(void *param)
{
    t_game *game = (t_game *)param;
    raycasting(game);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
        {
            if (is_walkable(game->posX + game->dirX * MOVE_SPEED, game->posY))
                game->posX += game->dirX * MOVE_SPEED;
            if (is_walkable(game->posX, game->posY + game->dirY * MOVE_SPEED))
                game->posY += game->dirY * MOVE_SPEED;
        }
        if (keydata.key == MLX_KEY_S)
        {
            if (is_walkable(game->posX - game->dirX * MOVE_SPEED, game->posY))
                game->posX -= game->dirX * MOVE_SPEED;
            if (is_walkable(game->posX, game->posY - game->dirY * MOVE_SPEED))
                game->posY -= game->dirY * MOVE_SPEED;
        }
        if (keydata.key == MLX_KEY_A)
        {
            double oldDirX = game->dirX;
            game->dirX = game->dirX * cos(ROT_SPEED) - game->dirY * sin(ROT_SPEED);
            game->dirY = oldDirX * sin(ROT_SPEED) + game->dirY * cos(ROT_SPEED);
            double oldPlaneX = game->planeX;
            game->planeX = game->planeX * cos(ROT_SPEED) - game->planeY * sin(ROT_SPEED);
            game->planeY = oldPlaneX * sin(ROT_SPEED) + game->planeY * cos(ROT_SPEED);
        }
        if (keydata.key == MLX_KEY_D)
        {
            double oldDirX = game->dirX;
            game->dirX = game->dirX * cos(-ROT_SPEED) - game->dirY * sin(-ROT_SPEED);
            game->dirY = oldDirX * sin(-ROT_SPEED) + game->dirY * cos(-ROT_SPEED);
            double oldPlaneX = game->planeX;
            game->planeX = game->planeX * cos(-ROT_SPEED) - game->planeY * sin(-ROT_SPEED);
            game->planeY = oldPlaneX * sin(-ROT_SPEED) + game->planeY * cos(-ROT_SPEED);
        }
    }
}

int main(void)
{
    t_game game;

    int start_direction = 'S';
    game.posX = 1.5;
    game.posY = 2.5;
    switch (start_direction)
    {
        case 'N': // Norte
            game.dirX = 0;
            game.dirY = -1;
            game.planeX = (game.dirX * COS90 - game.dirY * SIN90) * FOV;
            game.planeY = game.dirX * SIN90 + game.dirY * COS90;
            break;
        case 'S': // Sur
            game.dirX = 0;
            game.dirY = 1;
            game.planeX = (game.dirX * COS90 - game.dirY * SIN90) * FOV;
            game.planeY = game.dirX * SIN90 + game.dirY * COS90;
            break;
        case 'E': // Este
            game.dirX = 1;
            game.dirY = 0;
            game.planeX = game.dirX * COS90 - game.dirY * SIN90;
            game.planeY = (game.dirX * SIN90 + game.dirY * COS90) * FOV;
            break;
        case 'W': // Oeste
            game.dirX = -1;
            game.dirY = 0;
            game.planeX = game.dirX * COS90 - game.dirY * SIN90;
            game.planeY = (game.dirX * SIN90 + game.dirY * COS90) * FOV;
            break;
        default:
            return (puts("Invalid start direction"), 1);
    }

    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D Textured Raycaster", true);
    if (!game.mlx)
        return (puts("MLX Init failed"), 1);

    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game.img)
        return (puts("Failed to create image"), 1);

    // Cargar la textura PNG
    game.wall_texture = mlx_load_png("wall.png");
    if (!game.wall_texture)
        return (puts("Failed to load texture"), 1);

    mlx_loop_hook(game.mlx, render_frame, &game);
    mlx_key_hook(game.mlx, key_hook, &game);
    mlx_loop(game.mlx);

    mlx_delete_texture(game.wall_texture);
    mlx_terminate(game.mlx);
    return (0);
}
