#include "../cub3d.h"

static int check_player_position(char **map, int x, int y, t_player *player)
{
    if (ft_strchr("SWEN", map[y][x]))
    {
        player->x = x + 0.5; // Set player x-coordinate (center of the tile)
        player->y = y + 0.5; // Set player y-coordinate
        player->dir = map[y][x]; // Set player direction
        return 1; // Found a player position
    }
    return 0; // No player position found
}

// Validate player presence
bool validate_player_presence(char **map, t_player *player)
{
    int player_count;
    int y;
    int x;

    player_count = 0;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            player_count += check_player_position(map, x, y, player);
            x++;
        }
        y++;
    }
    if (player_count != 1)
    {
        handle_error("Invalid number of starting positions");
        return false;
    }
    return true;
}

// Validate file content
bool check_file_content(t_map_file_data *mfd)
{
    if (!mfd->north_texture || !mfd->south_texture ||
        !mfd->west_texture || !mfd->east_texture ||
        !mfd->floor_color || !mfd->ceiling_color)
        handle_error("Missing essential map data");
    // will need the below part for checking if able to open texture files,
    // but for now it's a comment for testing and debugging purposes

    // if (open(mfd->north_texture, O_RDONLY) == -1 ||
    //     open(mfd->south_texture, O_RDONLY) == -1 ||
    //     open(mfd->east_texture, O_RDONLY) == -1 ||
    //     open(mfd->west_texture, O_RDONLY) == -1)
    //     handle_error("Could not open texture files");
    return true;
}

// Wrapper to validate the entire map
bool validate_map(t_map_file_data *mfd, t_player *player)
{
    if (!check_file_content(mfd))
        return false;
    if (!check_colours_range(mfd->ceiling_color) || !check_colours_range(mfd->floor_color))
        return false;
    if (!validate_map_enclosure(mfd->map))
        return false;
    if (!validate_player_presence(mfd->map, player))
        return false;
    return true;
}