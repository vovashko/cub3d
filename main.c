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
	free(mfd->floor_color);
	free(mfd->ceiling_color);
	free(mfd);
}

void free_player(t_player *player)
{
	free(player);
}


int main (int argc, char **argv)
{
	
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
    
	t_game* game = (t_game *)malloc(sizeof(t_game));
    init_game(game, argv[1]);
	
	#if TEST_MODE == 2
	// printf("height %d\n", game->mfd->height - 1);
	// int i = 0;
	// while(i < game->mfd->height)
	// {
	// 	printf("the maps %d %s\n", i, game->mfd->map[i]);
	// 	i++;
	// }
	// printf("the floor color is %d %d %d\n", game->mfd->floor_color->r, game->mfd->floor_color->g, game->mfd->floor_color->b);
	// printf("the ceiling color is %d %d %d\n", game->mfd->ceiling_color->r, game->mfd->ceiling_color->g, game->mfd->ceiling_color->b);
	// printf("the north texture is %s\n", game->mfd->north_texture);
	// printf("the south texture is %s\n", game->mfd->south_texture);
	// printf("the west texture is %s\n", game->mfd->west_texture);
	// printf("the east texture is %s\n", game->mfd->east_texture);
	if(!map_check(game->mfd, game->player))
	{
		printf("Invalid map\n");
		return (1);
	}
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
	free_mfd(game->mfd);
	free(game);
    return (0);
}


// Adding my main, for checking purposes to call my parsing and validation functions
/*
	// static void print_textures_and_colors(const t_map_file_data *mfd)
// {
//     printf("Textures:\n");
//     printf("  North: %s\n", mfd->north_texture);
//     printf("  South: %s\n", mfd->south_texture);
//     printf("  West: %s\n", mfd->west_texture);
//     printf("  East: %s\n", mfd->east_texture);

//     printf("\nColors:\n");
//     printf("  Floor: %d, %d, %d\n", mfd->floor_color->r, mfd->floor_color->g, mfd->floor_color->b);
//     printf("  Ceiling: %d, %d, %d\n", mfd->ceiling_color->r, mfd->ceiling_color->g, mfd->ceiling_color->b);
// }

// static void print_map(char **map)
// {
//     printf("\nMap:\n");
//     for (int i = 0; map[i]; i++)
//     {
//         printf("%s\n", map[i]);
//     }
// }

int main(int argc, char **argv)
{
    t_map_file_data mfd = {0};
    t_player player = {0};

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./cub3d <map.cub>\n");
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    // printf("open file fd is: %d\n", fd);
    get_map_height(&mfd, fd);
    // printf("map height: %d\n", mfd.height);
    fd = open(argv[1], O_RDONLY);
    get_file_data(&mfd, fd);
    // print_map(mfd.map);
    // int i = 1;
    // while (mfd.map[i])
    // {
    //     printf("the map is: %c\n", *(mfd.map[i]));
    //     i++;
    // }

    if (!validate_map(&mfd, &player))
    {
        // printf("we are here\n");
        printf("Map validation failed.\n");
        free_mfd(&mfd);
        return EXIT_FAILURE;
    }

    printf("Map is valid.\n");

    // Print textures, colors, and map
    // print_textures_and_colors(&mfd);
    // print_map(mfd.map);

    // Free allocated memory
    free_mfd(&mfd);

    return EXIT_SUCCESS;
}


*/