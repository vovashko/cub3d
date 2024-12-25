/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/25 21:39:35 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

 #include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_floor_and_ceiling(t_game *game)
{
	int x;
	int y;
	int floor_color;
	int ceiling_color;
	

	floor_color = get_rgba(39, 245, 236, 255);
	ceiling_color = get_rgba(245, 121, 3, 255);

	x = 0;
	
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->background, x, y, ceiling_color);
			y++;
		}
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->background, x, y, floor_color);
			y++;
		}
		x++;
	}
}

void calculate_ray_data(t_ray *ray, t_player *player) {
    ray->x = player->dx - player->dy * RAD * ray->slice;
    ray->y = player->dy + player->dx * RAD * ray->slice;
    ray->delta_x = fabs(1 / ray->x);
    ray->delta_y = fabs(1 / ray->y);
    ray->hit_x = (int)player->x;
    ray->hit_y = (int)player->y;
    ray->angle = atan2(ray->y, ray->x);

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
            if (ray->dist_x < ray->dist_y)
            {
                ray->hit_distance[slice] = (ray->hit_x - player->x) / ray->x;
                ray->hit_portion = player->y + ray->hit_distance[slice] * ray->y;
                ray->hit_portion -= floor(ray->hit_portion);
                if (ray->hit_orientation == 'E' || ray->hit_orientation == 'W') {
                    ray->hit_portion = 1 - ray->hit_portion;
                }
            } else {
                ray->hit_distance[slice] = (ray->hit_y - player->y) / ray->y;
                ray->hit_portion = player->x + ray->hit_distance[slice] * ray->x;
                ray->hit_portion -= floor(ray->hit_portion);
                if (ray->hit_orientation == 'N' || ray->hit_orientation == 'S') {
                    ray->hit_portion = 1 - ray->hit_portion;
                }
            }
        printf("hit portion: %f\n", ray->hit_portion);
        printf("hit distance: %f\n", ray->hit_distance[slice]);
            break;
        }
    }
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


// void draw_wall(t_game *game, int x, int y, int ceiling_end, int floor_start) {
//     double scale = (double)TEXTURE_HEIGHT / game->ray->hit_y;
//     double texture_pos = (ceiling_end - HEIGHT / 2 + game->ray->hit_y / 2) * scale;
//     int texture_x = (int)(game->ray->hit_x * (double)TEXTURE_WIDTH) % TEXTURE_WIDTH;

//     while (y < floor_start) {
//         int texture_y = (int)texture_pos % TEXTURE_HEIGHT;
//         texture_pos += scale;

//         // Fetch the color from the texture
//         int wall_color = get_textured_color(game->ray->hit_orientation);

//         // Draw the pixel
//         mlx_put_pixel(game->background, x, y, wall_color);
//         y++;
//     }
// }

void zoom_out(t_game *game, int x, int slice_height) {
    uint32_t	rest;
	// double		ratio;
	uint32_t	i = 0;

    rest = (HEIGHT - slice_height) / 2;
    // ratio = (double)TEXTURE_HEIGHT / slice_height;

    // Define colors
    int ceiling_color = get_rgba(245, 121, 3, 255);   // Orange
    int floor_color = get_rgba(39, 245, 236, 255);    // Cyan

        while (i < rest)
        {
            mlx_put_pixel(game->background, x, i, ceiling_color);
            i++;
        }
        while (i < HEIGHT - rest)
        {
            mlx_put_pixel(game->background, x, i, get_textured_color(game->ray->hit_orientation));
            i++;
        }
        while (i < HEIGHT)
        {
            mlx_put_pixel(game->background, x, i, floor_color);
            i++;
        }
}


void draw_wall_slice(t_game *game, int x, t_ray *ray) {

    ray->slice_height = (uint32_t)(HEIGHT / ray->hit_distance[ray->slice]);
    ray->texture_x = (int)(ray->hit_portion * TEXTURE_WIDTH);  
    if (ray->slice_height > HEIGHT)
        ray->slice_height = HEIGHT;
    zoom_out(game, x, ray->slice_height);
}

    
//     int ceiling_end = (HEIGHT / 2) - (game->ray->hit_y / 2);
//     int floor_start = (HEIGHT / 2) + (game->ray->hit_y / 2);

//     ceiling_end = ceiling_end < 0 ? 0 : ceiling_end;
//     floor_start = floor_start >= HEIGHT ? HEIGHT - 1 : floor_start;

//     // Define colors
//     int ceiling_color = get_rgba(245, 121, 3, 255);   // Orange
//     int floor_color = get_rgba(39, 245, 236, 255);    // Cyan

//     while (y < HEIGHT)
//     {
//         if (y < ceiling_end)
//             mlx_put_pixel(game->background, x, y, ceiling_color);
//         else if (y >= ceiling_end && y < floor_start)
//             draw_wall(game, x, y, ceiling_end, floor_start);
//         else if (y >= floor_start)
//             mlx_put_pixel(game->background, x, y, floor_color);
//         y++;
//     }
// }

// void get_wall_height(t_ray *ray)
// {
    

// }


void	render(void *param)
{
	uint32_t	x;
	t_game		*game;

	game = param;
    game->ray->shift_factor = FOV_FACTOR;

	x = WIDTH;
	while (x--)
	{
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
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, render, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}