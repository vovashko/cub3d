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
	
	
	// draw_floor_and_ceiling(game);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);    // stretch image based on window size changing
	
	// raycaster(game->player, game->ray, game->map, game);
    render(game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, render, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}