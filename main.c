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

void free_mfd(t_map_file_data *mfd)
{
	int i;

	i = 0;
	while (i < mfd->height)
	{
		free(mfd->map[i]);
		i++;
	}
	free(mfd->map);
	free(mfd->north_texture);
	free(mfd->south_texture);
	free(mfd->west_texture);
	free(mfd->east_texture);
	free(mfd->floor_color_config);
	free(mfd->ceiling_color_config);
	free(mfd);
}

void free_player(t_player *player)
{
	free(player);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	key_hooks(game);
	update_player(game);
	raycast_and_render(game);
}


int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./cub3d <map.cub>\n");
        return EXIT_FAILURE;
    }
	t_game* game = (t_game *)malloc(sizeof(t_game));
    init_game(game, argv[1]);

    if (!validate_map(game->mfd, game->player))
    {
        printf("Map validation failed.\n");
        free_mfd(game->mfd);
        return EXIT_FAILURE;
    }
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	// stretch image based on window size changing
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

    free_mfd(game->mfd);

    return EXIT_SUCCESS;
}

