/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_checks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 12:25:10 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:25:27 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_surrounded_by_walls_or_spaces(char **map, size_t x, int y, int rows, size_t cols)
{
    // Check the left, right, top, and bottom neighbors
    if (x > 0 && map[y][x - 1] != '1' && map[y][x - 1] != ' ') // Left
        return false;
    if (x < cols - 1 && map[y][x + 1] != '1' && map[y][x + 1] != ' ') // Right
        return false;
    if (y > 0 && map[y - 1][x] != '1' && map[y - 1][x] != ' ') // Top
        return false;
    if (y < rows - 1 && map[y + 1][x] != '1' && map[y + 1][x] != ' ') // Bottom
        return false;

    return true;
}

// Function to check if the map is properly enclosed
bool check_enclosure(char **map, int rows, size_t cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (map[i][j] == ' ')
            {
                // Check if the space is surrounded by walls or other spaces
                if (!is_surrounded_by_walls_or_spaces(map, j, i, rows, cols))
                {
                    printf("Invalid map: space at (%d, %zu) is not surrounded by walls or other spaces\n", i, j);
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_top_and_bottom(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

