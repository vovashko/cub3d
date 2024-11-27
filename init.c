/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:21 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/27 16:01:33 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game, char *map_file)
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
	if (mlx_resize_image(game->player->player_img, 50, 50)== false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	 if (game->player->player_img == NULL)
    {
        printf("Error\nFailed to create player image\n");
        exit(1);
    }
	#if TEST_MODE == 1
	game->player->player_img->enabled = false;
	#endif 

	game->wall = mlx_texture_to_image(game->mlx, mlx_load_png("textures/west.png"));
	if (mlx_resize_image(game->wall, 50, 50)== false)
	{
		printf("Error\nFailed to resize image\n");
		exit(1);
	}
	game->player->x = 5 * 50;
	game->player->y = 5 * 50;
	game->player->dir = 0;
	game->player->dx = cos(game->player->dir) * 5;
	game->player->dy = sin(game->player->dir) * 5;
	game->player->fov = PI / 3;
	game->map = (int *)malloc(sizeof(int) * 100);
	#if TEST_MODE == 1
	init_map(map_file, game);
	#endif
	#if TEST_MODE == 0
	int map[100] = {
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};
	for (int i = 0; i < 100; i++)
	{
		game->map[i] = map[i];
	};
	(void)map_file;
	#endif
}
	
void init_map(char *file, t_game *game)
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFailed to open file\n");
		exit(1);
	}
	char *line = get_next_line(fd);
	int i = 0;
	while (get_next_line(fd))
	{
		if (line[0] == '1' || line[0] == '0')
		{
			for (int j = 0; j < 10; j++)
			{
				game->map[i] = line[j] - '0';
				i++;
			}
		}
		free(line);
	}
	close(fd);
}