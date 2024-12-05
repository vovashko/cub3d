/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:21 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/05 16:30:51 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_game *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	#if TEST_MODE == 1
	game->player->player_img = mlx_texture_to_image(game->mlx,
			mlx_load_png("textures/south.png"));
	if (mlx_resize_image(game->player->player_img, 50, 50) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	if (game->player->player_img == NULL)
	{
		printf("Error\nFailed to create player image\n");
		exit(1);
	}

	game->player->player_img->enabled = false;

	game->wall = mlx_texture_to_image(game->mlx,
			mlx_load_png("textures/west.png"));
	if (mlx_resize_image(game->wall, 50, 50) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	#endif
	game->player->x = -1;
	game->player->y = -1;
	game->player->dir = 0;
	game->player->dx = cos(game->player->dir) * 5;
	game->player->dy = sin(game->player->dir) * 5;
	game->player->fov = PI / 3;
}


void	init_game(t_game *game, char *map_file)
{
	
#if TEST_MODE == 1
	mlx_texture_t	*texture;
	
	
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	texture = mlx_load_png("textures/north.png");
	game->background = mlx_texture_to_image(game->mlx, texture);
	if (mlx_resize_image(game->background, WIDTH, HEIGHT) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->player_img = mlx_texture_to_image(game->mlx,
			mlx_load_png("textures/south.png"));
	if (mlx_resize_image(game->player->player_img, 50, 50) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	if (game->player->player_img == NULL)
	{
		printf("Error\nFailed to create player image\n");
		exit(1);
	}

	game->player->player_img->enabled = false;

	game->wall = mlx_texture_to_image(game->mlx,
			mlx_load_png("textures/west.png"));
	if (mlx_resize_image(game->wall, 50, 50) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	game->player->x = 5;
	game->player->y = 5;
	game->player->dir = 0;
	game->player->dx = cos(game->player->dir) * 5;
	game->player->dy = sin(game->player->dir) * 5;
	game->player->fov = PI / 3;
#endif
#if TEST_MODE == 2
	init_mfd(game, map_file);
	init_player(game);
#endif
#if TEST_MODE == 0
	int map[100] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1,
	};
	for (int i = 0; i < 100; i++)
	{
		game->map[i] = map[i];
	};
	(void)map_file;
#endif
}



