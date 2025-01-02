/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:21 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/02 16:32:26 by vshkonda      ########   odam.nl         */
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
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->player->dx = 1;
	game->player->dy = 0;
}


void	init_game(t_game *game, char *map_file)
{
	
#if TEST_MODE == 0
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
			mlx_load_png("textures/north.png"));
	if (mlx_resize_image(game->player->player_img, TILE_SIZE / 4, TILE_SIZE / 4) == false)
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
	if (mlx_resize_image(game->wall, TILE_SIZE, TILE_SIZE) == false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	game->player->x = 2 + 0.5;
	game->player->y = 2 + 0.5;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->player->dx = 1; // equivalent to 1
	game->player->dy = 0; // equivalent to 1
#endif
#if TEST_MODE == 2
	init_mfd(game, map_file);
	init_player(game);
#endif
#if TEST_MODE == 0
	game->map = (int *)malloc(sizeof(int) * 100);
	int map[100] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		
	};
	for (int i = 0; i < 100; i++)
	{
		game->map[i] = map[i];
	};
	(void)map_file;
#endif

	t_ray *ray = (t_ray *)malloc(sizeof(t_ray));
	ray->slice = WIDTH;
	ray->dx = 0;
	ray->dy = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->dist_x = 0;
	ray->dist_y = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->step_dir_x = 0;
	ray->step_dir_y = 0;
	ray->hit_portion = 0;
	game->ray = ray;
	ray->walls = (t_walls *)malloc(sizeof(t_walls));
	ray->walls->north = mlx_load_png("textures/north.png");
	ray->walls->south = mlx_load_png("textures/south.png");
	ray->walls->west =mlx_load_png("textures/west.png");
	ray->walls->east =mlx_load_png("textures/east.png");
	
	
}

// void	init_mfd(t_game *game, char *map_file)
// {
// 	game->mfd = (t_map_file_data *)malloc(sizeof(t_map_file_data));
// 	game->mfd->file = map_file;
// 	game->mfd->width = 0;
// 	game->mfd->height = 0;
// 	game->mfd->floor_color = (t_color *)malloc(sizeof(t_color));
// 	game->mfd->floor_color->r = -1;
// 	game->mfd->floor_color->g = -1;
// 	game->mfd->floor_color->b = -1;
// 	game->mfd->ceiling_color = (t_color *)malloc(sizeof(t_color));
// 	game->mfd->ceiling_color->r = -1;
// 	game->mfd->ceiling_color->g = -1;
// 	game->mfd->ceiling_color->b = -1;
// 	game->mfd->north_texture = NULL;
// 	game->mfd->south_texture = NULL;
// 	game->mfd->west_texture = NULL;
// 	game->mfd->east_texture = NULL;
// 	game->mfd->map = NULL;
// 	if (check_file_content(game->mfd) == false)
// 	{
// 		handle_error("Invalid file content");
// 		free_mfd(game->mfd);
// 		exit(1);
// 	}
// }