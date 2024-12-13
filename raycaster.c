/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 18:12:37 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

// for raycaster need to adjust width and height after window resize
// mlx_delete_image
// side_dist - distance until the wall (I supose)
// draw floor and ceiling (splitting the window in half and draw the respective color)
// mlx_resize_hook - resize the window after first raycast

 

void raycaster(t_game *game, t_ray * ray)
{
	int ray_num = 0;

	while (ray_num < WIDTH)
	{
		init_ray(ray, game->player, ray_num);
		calculate_offset(ray);
		measure_distance_to_wall(ray, game->map);
		get_wall_height(ray);
		draw_wall(ray, game);
	}
}

int main()
{

	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");
	
	
	draw_map(game);
	raycaster(game->player, game->ray, game->map, game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}