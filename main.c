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

int main (int argc, char **argv)
{
	t_game* game = (t_game *)malloc(sizeof(t_game));
	#if TEST_MODE == 1
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
	#endif
    #if TEST_MODE == 1
    init_game(game, argv[1]);
	#endif
	#if TEST_MODE == 0
	(void)argc;
	(void)argv;
	init_game(game, "map.cub");
	#endif
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