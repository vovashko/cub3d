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

// void	color_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
// {
// 	uint32_t	*pixel;

// 	if (!image || x >= image->width || y >= image->height)
// 		return ;
// 	pixel = (uint32_t *)image->pixels;
// 	pixel[y * image->width + x] = color;
// }

// void zoom_in (t_game *data, t_ray *ray, int x)
// {
//     uint32_t start;
//     double ratio;
//     uint32_t i;
//     uint32_t color;

//     start = ((double)ray->slice_height - HEIGHT) * TILE_SIZE / ray->slice_height / 2;
//     ratio = (double)TILE_SIZE / ray->slice_height;
//     (void)ratio;
//     (void)start;
//     i = 0;
//     while (i < HEIGHT)
//     {
//         color = get_textured_color(ray->hit_orientation);
// 		color_pixel(data->background, x, i++, color);
//     }
// }

// static void	zoom_out(t_game *data, t_ray *ray, int x)
// {
// 	uint32_t	rest;
// 	double		ratio;
// 	uint32_t	i;
// 	uint32_t	color;
//     int ceiling_color = get_rgba(245, 121, 3, 255);   // Orange
//     int floor_color = get_rgba(39, 245, 236, 255);    // Cyan

// 	rest = (HEIGHT - ray->slice_height) / 2;
// 	ratio = (double)TILE_SIZE / ray->slice_height;
//     (void)ratio;
// 	i = 0;
// 	while (i < rest)
// 		color_pixel(data->background, x, i++, ceiling_color);
// 	while (i < HEIGHT - rest)
// 	{
// 		color = get_textured_color(ray->hit_orientation);
// 		color_pixel(data->background, x, i++, color);
// 	}
// 	while (i < HEIGHT)
// 		color_pixel(data->background, x, i++, floor_color);
// }

void draw_wall_slice(t_game *game, t_ray *ray) {
    int ceiling_color = get_rgba(245, 121, 3, 255);   // Orange
    int floor_color = get_rgba(39, 245, 236, 255);    // Cyan
    int wall_color = get_textured_color(ray->hit_orientation);
    int i = 0;

    while (i < WIDTH)
    {
        if (i < ray->wall_start)
            mlx_put_pixel(game->background, ray->slice, i, ceiling_color);
        else if (i >= ray->wall_start && i <= ray->wall_end)
            mlx_put_pixel(game->background, ray->slice, i, wall_color);
        else
            mlx_put_pixel(game->background, ray->slice, i, floor_color);
        i++;
    }
}



int get_map_value(int *map, int x, int y) {
    return map[y * 10 + x]; // Assuming map width is 10
}

int perform_dda(t_ray *ray, int *map) {
    int hor = 0;
    
    while (1) {
        if (ray->dist_x < ray->dist_y) {
            ray->dist_x += ray->delta_x;
            ray->hit_x += ray->x_dir;
            hor = 1;
        } else {
            ray->dist_y += ray->delta_y;
            ray->hit_y += ray->y_dir;
            hor = 0;
        }
        // Check if the ray hits a wall
        if (get_map_value(map, ray->hit_x, ray->hit_y) == 1) {
            break;
        }
    }
    return hor;
}

void calculate_wall_height(t_ray *ray, int hor) {
    if (hor == 0)
            ray->hit_distance = ray->dist_x - ray->delta_x;
    else
            ray->hit_distance = ray->dist_y - ray->delta_y;
    ray->slice_height = (uint32_t)((double)HEIGHT / ray->hit_distance);
    ray->wall_start = HEIGHT / 2 - ray->slice_height / 2;
    if (ray->wall_start < 0)
        ray->wall_start = 0;
    ray->wall_end = ray->slice_height / 2 + HEIGHT / 2;
    if (ray->wall_end >= HEIGHT)
        ray->wall_end = HEIGHT - 1;
    ray->hit_orientation = hor ? (ray->y_dir == 1 ? 'N' : 'S') : (ray->x_dir == 1 ? 'W' : 'E');
}

void init_ray(t_ray *ray, t_player *player) {
    ray->camera_x = 2 * ray->slice / (double)WIDTH - 1;
    ray->x = player->dx - player->dy * ray->camera_x;
    ray->y = player->dy + player->dx * ray->camera_x;
    ray->hit_x = (int)player->x;
    ray->hit_y = (int)player->y;

    if (ray->y == 0)
        ray->delta_y = 1e30;
    else
        ray->delta_y = fabs(1 / ray->y);
    if (ray->x == 0)
        ray->delta_x = 1e30;
    else
        ray->delta_x = fabs(1 / ray->x);
    
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

// void calculate_texture(t_game *game, t_ray *ray)
// {

// }

void raycast_and_render(void *param) {
    t_game *game;
    int hor;

    game = param;
    game->ray->slice = WIDTH;
    // reset_window(game->background);
    while (game->ray->slice--) 
    {
        init_ray(game->ray, game->player);
        hor = perform_dda(game->ray, game->map);
        calculate_wall_height(game->ray, hor);
        draw_wall_slice(game, game->ray);
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
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, raycast_and_render, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	return (0);
}