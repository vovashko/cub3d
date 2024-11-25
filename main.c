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
        printf("Player walks forwards\n");
		game->player->y -= 1;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
        printf("Player walks backwards\n");
		game->player->y += 1;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        printf("Player walks left\n");
		game->player->x -= 1;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
        printf("Player walks right\n");
		game->player->x += 1;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        printf("Player turns left\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        printf("Player turns right\n");
        
}


int main (int argc, char **argv)
{
    // if (argc != 2)
    // {
    //     printf("Error\nInvalid number of arguments\n");
    //     return (1);
    // }

    // if (check_file_format(argv[1]) == false)
    // {
    //     printf("Error\nInvalid file format\nPlease provide a file with the .cub extension\n");
    //     return (1);
    // }
    (void)argc;
	(void)argv;
    t_game* game = (t_game *)malloc(sizeof(t_game));
    init_game(game);

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

    if (mlx_image_to_window(game->mlx, game->player->player_img, game->player->x, game->player->y) == -1)
    {
        printf("Error\nFailed to draw image\n");
        return (1);
    }


    mlx_loop_hook(game->mlx, key_hooks, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    
}