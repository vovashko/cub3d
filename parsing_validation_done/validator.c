#include "../cub3d.h"

bool ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return true;
    return false;
}

// Find the maximum row length
int get_max_width(char **map)
{
    int max_width = 0;
    int row_length;

    for (int i = 0; map[i]; i++)
    {
        row_length = ft_strlen(map[i]);
        if (row_length > max_width)
            max_width = row_length;
    }
    return max_width;
}

// Check if a row is empty or contains only spaces
bool is_empty_row(char *row)
{
    while (*row)
    {
        if (!ft_isspace(*row))
            return false;
        row++;
    }
    return true;
}

// Check the first and last characters of a row
bool is_row_enclosed(char *row, int row_index)
{
    int curr_len = ft_strlen(row);

    while (curr_len > 0 && ft_isspace(row[curr_len - 1]))
        curr_len--;
    if (row[0] != '1' || row[curr_len - 1] != '1')
    {
        // leaving the line below for now, for easier debugging if needed, but eventually will be a handle_error call
        fprintf(stderr, "Error: Row %d is not enclosed by walls.\n", row_index);
        return false;
    }
    return true;
}

// Validate gaps in the top or bottom rows
bool validate_edge_gaps(char *curr_row, char *adjacent_row, int is_top, int row_index)
{
    int curr_len = ft_strlen(curr_row);
    int adjacent_len = ft_strlen(adjacent_row);

    for (int j = 1; j < curr_len - 1; j++)
    {
        if ((curr_row[j] == ' ' &&
            adjacent_row && adjacent_row[j] != '1' && adjacent_row[j] != ' ' && curr_len <= adjacent_len) || ft_strchr("SWEN0", curr_row[j])) // added length check, because in maps/good/test_whitespace.cub, the rows end with spaces that would twist the results
        {
            // leaving the line below for now, for easier debugging if needed, but eventually will be a handle_error call
            fprintf(stderr, "Error: Gap in %s row is not supported by adjacent rows at row %d, column %d.\n",
                    is_top ? "top" : "bottom", row_index, j);
            return false;
        }
    }
    return true;
}

// Validate spaces in the middle rows
bool validate_middle_row_gaps(char *curr_row, char *row_on_top, char *row_on_bottom, int row_index)
{
    int curr_len = ft_strlen(curr_row);
    int top_len = row_on_top ? ft_strlen(row_on_top) : 0;
    int bottom_len = row_on_bottom ? ft_strlen(row_on_bottom) : 0;

    for (int j = 1; j < curr_len - 1; j++)
    {
        if (curr_row[j] == ' ')
        {
            char above = (j < top_len - 2) ? row_on_top[j] : ' '; // minus 2 to get rid of NULL and '\n' at the end of line
            char below = (j < bottom_len - 2) ? row_on_bottom[j] : ' '; //same here

            if ((above != '1' && above != ' ' && above != '\n' && above != '0') ||
                (below != '1' && below != ' ' && below != '\n' && below != '0'))
            {
                handle_error("Invalid gap in middle row at row %d, column %d.\n", row_index, j);
                return false;
            }
        }
    }
    return true;
}

void free_map(char **map, int rows)
{
    if (!map)
        return;

    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}

// Validate player presence
bool validate_player_presence(char **map, t_player *player)
{
    int player_count = 0;

    for (int y = 0; map[y]; y++)
    {
        for (int x = 0; map[y][x]; x++)
        {
            if (ft_strchr("SWEN", map[y][x]))
            {
                player->x = x + 0.5;
                player->y = y + 0.5;
                player->dir = map[y][x];
                player_count++;
            }
        }
    }
    if (player_count != 1)
    {
        handle_error("Invalid number of starting positions");
        return false;
    }
    return true;
}

// Validate map enclosure
bool validate_map_enclosure(char **map)
{
    int i = 0;
    int empty_row_detected = 0;

    if (!map || !map[0])
    {
        handle_error("Map is missing or empty.\n");
        return 0;
    }

    while (map[i])
    {
        char *curr_row = map[i];
        char *row_on_top = (i > 0) ? map[i - 1] : NULL;
        char *row_on_bottom = map[i + 1];

        // Check for floating rows
        if (is_empty_row(curr_row))
        {
            empty_row_detected = 1;
            i++;
            continue;
        }
        else if (empty_row_detected)
        {
            handle_error("Map contains floating or disconnected rows.\n");
            return false;
        }

        // Check if the row is enclosed
        if (!is_row_enclosed(curr_row, i))
            return false;

        // Validate edge rows
        if (i == 0 && !validate_edge_gaps(curr_row, row_on_bottom, 1, i))
        {
            return false;
        }
        if (!row_on_bottom && !validate_edge_gaps(curr_row, row_on_top, 0, i))
        {
            return false;
        }

        // Validate gaps in middle rows
        if (row_on_top && row_on_bottom &&
            !validate_middle_row_gaps(curr_row, row_on_top, row_on_bottom, i))
            return false;

        i++;
    }

    return true; // Map is valid
}

//Validate file content
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

//Validate colours range
bool check_colours_range(t_color *color)
{
    if (color == NULL)
        return false;
    if (color->r < 0 || color->r > 255)
        return false;
    if (color->g < 0 || color->g > 255)
        return false;
    if (color->b < 0 || color->b > 255)
        return false;
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