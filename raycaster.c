/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/18 18:35:11 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// for raycaster need to adjust width and height after window resize
// mlx_delete_image
// side_dist - distance until the wall (I supose)
// draw floor and ceiling (splitting the window in half and draw the respective color)
// mlx_resize_hook - resize the window after first raycast

 

// void raycaster(t_game *game, t_ray * ray)
// {
// 	int ray_num = 0;

// 	while (ray_num < WIDTH)
// 	{
// 		init_ray(ray, game->player, ray_num);
// 		calculate_offset(ray);
// 		measure_distance_to_wall(ray, game->map);
// 		get_wall_height(ray);
// 		draw_wall(ray, game);
// 	}
// }
// void check_horizontal(t_ray *ray, t_player *player, t_map_file_data *mfd)
// {
// }


// void measure_distance_to_wall(t_ray *ray, t_game *game)
// {
	
// }


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

void calculate_ray_data(t_ray *ray, t_player *player, float shift_factor) {
    ray->x = player->dx - player->dy * shift_factor;
    ray->y = player->dy + player->dx * shift_factor;
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

void perform_dda(t_ray *ray, int **map) {
    while (1) {
        if (ray->dist_x < ray->dist_y) {
            ray->dist_x += ray->delta_x;
            ray->hit_x += ray->x_dir;
        } else {
            ray->dist_y += ray->delta_y;
            ray->hit_y += ray->y_dir;
        }
        if (map[ray->hit_y][ray->hit_x] == 1) { // Wall hit
            ray->hit_distance = (ray->dist_x < ray->dist_y) ? ray->dist_x : ray->dist_y;
            break;
        }
    }
}

void draw_wall_slice(t_ray *ray, t_game *game) {
    float wall_height = HEIGHT / ray->hit_distance;
    int draw_start = (HEIGHT / 2) - (wall_height / 2);
    int draw_end = (HEIGHT / 2) + (wall_height / 2);
    draw_start = draw_start < 0 ? 0 : draw_start;
    draw_end = draw_end >= HEIGHT ? HEIGHT - 1 : draw_end;

    for (int y = draw_start; y <= draw_end; y++) {
        mlx_put_pixel(game->background, ray->slice, y, 0x00FF00FF);
    }
}

void raycaster(void *params) {
	t_game *game = (t_game *)params;
	t_ray *ray;
	ray = game->ray;
    ray->slice = WIDTH;
    ray->shift_factor = FOV / WIDTH;

    while (ray->slice--) {
        calculate_ray_data(ray, game->player, ray->shift_factor);
        perform_dda(ray, &game->map);
        draw_wall_slice(ray, game);
        ray->shift_factor -= FOV / WIDTH;
    }
}

int main()
{

	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");
	
	
	draw_floor_and_ceiling(game);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);    // stretch image based on window size changing
	
	// raycaster(game->player, game->ray, game->map, game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, raycaster, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}