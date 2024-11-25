// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   main.c                                             :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/11/25 13:46:29 by vshkonda      #+#    #+#                 */
// /*   Updated: 2024/11/25 14:06:43 by vshkonda      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"



void key_hooks(void *params)
{
    t_game *game = (t_game *)params;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->y += game->player->dy;
		game->player->x += game->player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->y -= game->player->dy;
		game->player->x -= game->player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x -= 5;
		game->player->y += 5;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x += game->player->dx;
		game->player->y -= game->player->dy;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        {
			game->player->dir -= 0.1;
			if (game->player->dir < 0)
				game->player->dir += 2 * PI;
			game->player->dx = cos(game->player->dir) * 5;
			game->player->dy = sin(game->player->dir) * 5;
		}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		{
			game->player->dir += 0.1;
			if (game->player->dir > 2 * PI)
				game->player->dir -= 2 * PI;
			game->player->dx = cos(game->player->dir) * 5;
			game->player->dy = sin(game->player->dir) * 5;
		}
	
    
}

void update_player(void *params)
{
	t_game *game = (t_game *)params;
	if (mlx_image_to_window(game->mlx, game->player->player_img, game->player->x, game->player->y) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}

}

void draw_map(t_game *game)
{
	int x = 0;
	int y = 0;
	int i = 0;
	while (y < 10)
	{
		while (x < 10)
		{
			if (game->map[i] == 1)
			{
				if (mlx_image_to_window(game->mlx, game->wall, x * 50, y * 50) == -1)
				{
					printf("Error\nFailed to draw image\n");
					exit(1);
				}
			}
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\nInvalid number of arguments\n");
        return (1);
    }

    if (check_file_format(argv[1]) == false)
    {
        printf("Error\nInvalid file format\nPlease provide a file with the .cub extension\n");
        return (1);
    }
    t_game* game = (t_game *)malloc(sizeof(t_game));
    init_game(game, argv[1]);

	if (game->player->player_img == NULL)
    {
        printf("Error\nplayer_img is NULL\n");
        return (1);
    }

	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		return (1);
	}
	draw_map(game);

    mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    
}