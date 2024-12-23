#include "cub3d.h"
// Adding my main, for checking purposes to call my parsing and validation functions

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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./cub3d <map.cub>\n");
        return EXIT_FAILURE;
    }
    t_game *game = (t_game *)malloc(sizeof(t_game));
    init_game(game, argv[1]);

    if (!validate_map(game->mfd, game->player))
    {
        printf("Map validation failed.\n");
        free_mfd(game->mfd);
        return EXIT_FAILURE;
    }
    printf("Map is valid.\n");

    // Print textures, colors, and map
    // print_textures_and_colors(game->mfd);
    // print_map(game->mfd->map);

    // Free allocated memory
    free_mfd(game->mfd);

    return EXIT_SUCCESS;
}