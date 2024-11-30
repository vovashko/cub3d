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
	#if TEST_MODE == 2
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
    #if TEST_MODE == 2
    init_game(game, argv[1]);
	int i = 0;
	while(i < game->mfd->height)
	{
		printf("the maps %s\n", game->mfd->map[i]);
		i++;
	}
	printf("the floor color is %d %d %d\n", game->mfd->floor_color->r, game->mfd->floor_color->g, game->mfd->floor_color->b);
	printf("the ceiling color is %d %d %d\n", game->mfd->ceiling_color->r, game->mfd->ceiling_color->g, game->mfd->ceiling_color->b);
	printf("the north texture is %s\n", game->mfd->north_texture);
	printf("the south texture is %s\n", game->mfd->south_texture);
	printf("the west texture is %s\n", game->mfd->west_texture);
	printf("the east texture is %s\n", game->mfd->east_texture);
	#endif
	#if TEST_MODE == 0
	(void)argc;
	(void)argv;
	init_game(game, "map.cub");
	
	#endif

	#if TEST_MODE == 1
	draw_map(game);

    mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	#endif
    return (0);
}
