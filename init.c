/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:21 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/25 15:15:12 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx_texture_t *texture = mlx_load_png("textures/north.png");
	
	game->background = mlx_texture_to_image(game->mlx, texture);
	if (mlx_resize_image(game->background, WIDTH, HEIGHT)== false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->player_img = mlx_texture_to_image(game->mlx, mlx_load_png("textures/south.png"));
	if (mlx_resize_image(game->player->player_img, WIDTH / 2, HEIGHT / 2)== false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	 if (game->player->player_img == NULL)
    {
        printf("Error\nFailed to create player image\n");
        exit(1);
    }
	game->player->x = 5;
	game->player->y = 5;
	game->player->dir = 0;
	// game->map = (int *)malloc(sizeof(int) * 100);
	
	// int temp_map[100] = {
	// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	// 	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	// };

	// for (int i = 0; i < 100; i++) {
	// 	game->map[i] = temp_map[i];
	// }
}
	
    