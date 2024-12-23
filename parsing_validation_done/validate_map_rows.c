#include "../cub3d.h"

// Check the first and last characters of a row
bool is_row_enclosed(char *row)
{
    int curr_len = ft_strlen(row);

    while (curr_len > 0 && ft_isspace(row[curr_len - 1]))
        curr_len--;
    if (row[0] != '1' || row[curr_len - 1] != '1')
    {
        // leaving the line below for now, for easier debugging if needed, but eventually will be a handle_error call
        handle_error("Error: Row is not enclosed by walls.");
        return false;
    }
    return true;
}

// Validate gaps in the top or bottom rows
bool validate_edge_gaps(char *curr_row, char *adjacent_row)
{
    int curr_len;
    int adjacent_len;
    int j;

    curr_len = ft_strlen(curr_row);
    adjacent_len = ft_strlen(adjacent_row);
    j = 1;
    while (j < curr_len - 1)
    {
        if ((curr_row[j] == ' ' &&
             adjacent_row && adjacent_row[j] != '1' && adjacent_row[j] != ' ' && curr_len <= adjacent_len) ||
            ft_strchr("SWEN0", curr_row[j])) // added length check, because in maps/good/test_whitespace.cub, the rows end with spaces that would twist the results
        {
            handle_error("Error: Gap in row is not supported by adjacent rows.");
            return false;
        }
        j++;
    }
    return true;
}

static bool validate_gap(char *row_on_top, char *row_on_bottom, int top_len, int j)
{
    int bottom_len;
    char above;
    char below;

    bottom_len = ft_strlen(row_on_bottom);
    if (j < top_len - 2)
        above = row_on_top[j];
    else
        above = ' ';
    if (j < bottom_len - 2)
        below = row_on_bottom[j];
    else
        below = ' ';
    if ((above != '1' && above != ' ' && above != '\n' && above != '0') ||
        (below != '1' && below != ' ' && below != '\n' && below != '0'))
    {
        handle_error("Invalid gap in middle row.");
        return false;
    }
    return true;
}

// Validate spaces in the middle rows
bool validate_middle_row_gaps(char *curr_row, char *row_on_top, char *row_on_bottom)
{
    int curr_len;
    int top_len;
    int j;

    j = 1;
    curr_len = ft_strlen(curr_row);
    top_len = ft_strlen(row_on_top);
    while (j < curr_len - 1)
    {
        if (curr_row[j] == ' ')
            if (!validate_gap(row_on_top, row_on_bottom, top_len, j))
                return false;
        j++;
    }
    return true;
}
