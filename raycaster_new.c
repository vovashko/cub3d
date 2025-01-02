#define MAP_WIDTH 10
#define MAP_HEIGHT 10


#include <stdlib.h>
#include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_game {
    void    *mlx;
    void    *window;
    int     screen_width;
    int     screen_height;
} t_game;

void    init_game(t_game *game, int width, int height) {
    game->mlx = mlx_init();
    if (!game->mlx) {
        fprintf(stderr, "Error initializing mlx\n");
        exit(EXIT_FAILURE);
    }
    game->screen_width = width;
    game->screen_height = height;
    game->window = mlx_new_window(game->mlx, width, height, "Raycaster");
    if (!game->window) {
        fprintf(stderr, "Error creating window\n");
        exit(EXIT_FAILURE);
    }
}

typedef struct s_player {
    double x;      // Player's x position
    double y;      // Player's y position
    double dir_x;  // Direction vector (x)
    double dir_y;  // Direction vector (y)
    double plane_x; // Camera plane (x)
    double plane_y; // Camera plane (y)
} t_player;

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void init_player(t_player *player) {
    player->x = 2.0;
    player->y = 2.0;
    player->dir_x = -1.0; // Facing west
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.66; // FOV
}



void raycast(t_game *game, t_player *player) {
    for (int x = 0; x < game->screen_width; x++) {
        double camera_x = 2 * x / (double)game->screen_width - 1; // X-coordinate in camera space
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        int map_x = (int)player->x;
        int map_y = (int)player->y;

        double side_dist_x, side_dist_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        int step_x, step_y;
        int hit = 0;
        int side;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (player->x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (player->y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
        }

        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] > 0) hit = 1;
        }

        if (side == 0) perp_wall_dist = (map_x - player->x + (1 - step_x) / 2) / ray_dir_x;
        else perp_wall_dist = (map_y - player->y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(game->screen_height / perp_wall_dist);

        int draw_start = -line_height / 2 + game->screen_height / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + game->screen_height / 2;
        if (draw_end >= game->screen_height) draw_end = game->screen_height - 1;

        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF; // Shade walls differently
        for (int y = draw_start; y <= draw_end; y++) {
            mlx_pixel_put(game->mlx, game->window, x, y, color);
        }
    }
}

int game_loop(t_game *game, t_player *player) {
    mlx_clear_window(game->mlx, game->window);
    raycast(game, player);
    return (0);
}

int main(void) {
    t_game game;
    t_player player;

    init_game(&game, 800, 600);
    init_player(&player);
    mlx_loop_hook(game.mlx, (void *)game_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}
