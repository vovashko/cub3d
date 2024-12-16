/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/16 16:26:18 by vovashko      ########   odam.nl         */
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
	draw_map(game);
	
	// raycaster(game->player, game->ray, game->map, game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}