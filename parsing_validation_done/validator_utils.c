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

void free_map(char **map, int rows)
{
    if (!map)
        return;

    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}