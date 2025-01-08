#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int get_textured_color(char orientation) {
    // Example: Blend the wall orientation color with texture coordinates
    int base_color;

    switch (orientation) {
        case 'N': base_color = get_rgba(255, 0, 0, 255); break; // Red for north
        case 'S': base_color = get_rgba(0, 255, 0, 255); break; // Green for south
        case 'E': base_color = get_rgba(0, 0, 255, 255); break; // Blue for east
        case 'W': base_color = get_rgba(255, 255, 0, 255); break; // Yellow for west
        default: base_color = get_rgba(255, 255, 255, 255); break; // White fallback
    }

    return base_color;
}

void draw_wall_slice(t_game *game, int x, t_ray *ray) {
    
    ray->slice_height = (int)((double)HEIGHT / ray->hit_distance[x]);
    ray->texture_x = (int)(ray->hit_portion * TILE_SIZE);
    if (ray->slice_height > HEIGHT)
        ray->slice_height = HEIGHT;
    
    int i = 0;
    int ceiling_end = (HEIGHT - ray->slice_height) / 2;
    int floor_start = (HEIGHT + ray->slice_height) / 2;
    ceiling_end = ceiling_end < 0 ? 0 : ceiling_end;
    floor_start = floor_start >= HEIGHT ? HEIGHT - 1 : floor_start;
    int ceiling_color = get_rgba(245, 121, 3, 255);   // Orange
    int floor_color = get_rgba(39, 245, 236, 255);    // Cyan

    while (i < ceiling_end) {
        mlx_put_pixel(game->background, x, i, ceiling_color);
        i++;
    }
    while (i < floor_start) {
        mlx_put_pixel(game->background, x, i, get_textured_color(game->ray->hit_orientation));
        i++;
    }
    while (i < HEIGHT) {
        mlx_put_pixel(game->background, x, i, floor_color);
        i++;
    }
}

void calculate_ray_data(t_ray *ray, t_player *player) {
    ray->x = player->dx - player->dy * ray->shift_factor;
    ray->y = player->dy + player->dx * ray->shift_factor;
    ray->delta_x = fabs(1 / ray->x);
    ray->delta_y = fabs(1 / ray->y);
    ray->hit_x = (int)player->x;
    ray->hit_y = (int)player->y;

    if (ray->x < 0) {
        ray->x_dir = -1;
        ray->dist_x = (player->x - ray->hit_x) * ray->delta_x;
    } else {
        ray->x_dir = 1;
        ray->dist_x = (ray->hit_x + 1.0 - player->x) * ray->delta_x;
    }
    if (ray->y < 0) {
        ray->y_dir = -1;
        ray->dist_y = (player->y - ray->hit_y) * ray->delta_y;
    } else {
        ray->y_dir = 1;
        ray->dist_y = (ray->hit_y + 1.0 - player->y) * ray->delta_y;
    }
    
}

int get_map_value(int *map, int x, int y) {
    return map[y * 10 + x]; // Assuming map width is 10
}

void perform_dda(t_ray *ray, int *map, int slice, t_player *player) {
    while (1) {
        if (ray->dist_x < ray->dist_y) {
            ray->dist_x += ray->delta_x;
            ray->hit_x += ray->x_dir;

            // Update hit orientation for vertical walls (east or west)
            ray->hit_orientation = (ray->x_dir > 0) ? 'E' : 'W';
        } else {
            ray->dist_y += ray->delta_y;
            ray->hit_y += ray->y_dir;

            // Update hit orientation for horizontal walls (north or south)
            ray->hit_orientation = (ray->y_dir > 0) ? 'S' : 'N';
        }

        // Check if the ray hits a wall
        if (get_map_value(map, ray->hit_x, ray->hit_y) == 1) {
            // Calculate hit distance based on which axis was crossed last
            break;
        }
    }
    if (ray->dist_x < ray->dist_y) 
        {
            ray->hit_distance[slice] = (ray->hit_x - player->x) * ray->x_dir;
            ray->hit_portion = player->y + ray->hit_distance[slice] * ray->y;
        } 
    else 
        {
            ray->hit_distance[slice] = (ray->hit_y - player->y) * ray->y_dir;
            ray->hit_portion = player->x + ray->hit_distance[slice] * ray->x;
        }
	ray->angle = atan2(ray->y - player->y, ray->x - player->x);
	player->view_angle = atan2(player->dy, player->dx);
	ray->hit_distance[slice] /= cos(player->view_angle - ray->angle);

}

void render(void *param) {
    uint32_t x;
    t_game *game;

    game = param;
    game->ray->shift_factor = FOV_FACTOR;

    x = WIDTH;
    while (x--) {
        calculate_ray_data(game->ray, game->player);
        perform_dda(game->ray, game->map, x, game->player);
        draw_wall_slice(game, x, game->ray);
        game->ray->shift_factor -= 2.0 * FOV_FACTOR / (WIDTH - 1.0);
    }
}

int main()
{

	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");
	
	
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);    // stretch image based on window size changing
	
    render(game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, render, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}

#define MAP_WIDTH 10
#define MAP_HEIGHT 10


#include <stdlib.h>
#include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
#include <math.h>

typedef struct s_game {
    void    *mlx;
    mlx_image_t    *image;
	int screen_width;
	int screen_height;
} t_game;

void    init_game(t_game *game, int width, int height) {
    game->mlx = mlx_init(width, height, "Raycaster", true);
    if (!game->mlx) {
        fprintf(stderr, "Error initializing mlx\n");
        exit(EXIT_FAILURE);
    }
	game->image = mlx_new_image(game->mlx, width, height);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	game->screen_height = height;
	game->screen_width = width;

}

typedef struct s_player {
    double x;      // Player's x position
    double y;      // Player's y position
    double dx;  // Direction vector (x)
    double dy;  // Direction vector (y)
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
    player->dx = 1.0; // Facing west
    player->dy = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.66; // FOV
}



void raycast(t_game *game, t_player *player) {
    for (int x = 0; x < game->screen_width; x++) {
        double camera_x = 2 * x / (double)game->screen_width - 1; // X-coordinate in camera space
        double ray_dir_x = player->dx + player->plane_x * camera_x;
        double ray_dir_y = player->dy + player->plane_y * camera_x;

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
            mlx_put_pixel(game->image, x, y, color);
        }
    }
}

static void turn_controls(t_game *game, t_player *player)
{
    double old_dx;
    double old_plane_x;
    double turn = 0.1; // Rotation angle

    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        turn = -turn; // Rotate left
    }
    else if (!mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        return; // No rotation
    }

    old_dx = player->dx;
    old_plane_x = player->plane_x;

    // Rotate direction vector
    player->dx = player->dx * cos(turn) - player->dy * sin(turn);
    player->dy = old_dx * sin(turn) + player->dy * cos(turn);

    // Rotate camera plane
    player->plane_x = player->plane_x * cos(turn) - player->plane_y * sin(turn);
    player->plane_y = old_plane_x * sin(turn) + player->plane_y * cos(turn);
}


void key_hooks(t_game *game, t_player *player)
{
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		player->y += player->dy;
		player->x += player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		player->y -= player->dy;
		player->x -= player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		player->x -= player->dy;
		player->y += player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		player->x += player->dy;
		player->y -= player->dx;
	}
	turn_controls(game, player);
}

int game_loop(t_game *game, t_player *player) {
    // mlx_clear_window(game->mlx);
    raycast(game, player);
	key_hooks(game, player);
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
