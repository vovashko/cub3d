/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 12:36:50 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/05 13:01:52 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t get_map_width(char **map, int rows)
{
	int y;
	size_t current_len;

	y = 0;
	size_t width = 0;
	
	while (y < rows)
	{
		printf("the map is %s\n", map[y]);
		current_len = ft_strlen(map[y]);
		if (current_len > width)
			width = current_len;
		y++;
	}
	return (width);
}

bool check_valid_chars(char **map, int rows)
{
	int i;
	int j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}


bool check_starting_pos(char **map, int height, t_player *player)
{
	int i;
	int j;

	i = 0;
	j = 0;
	player->y = -1;
	player->x = -1;
	while (i < height)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (player->y != -1 || player->x != -1)
					return (false);
				player->y = i;
				player->x = j;
			}
	
			j++;
		}
		i++;
	}
	return (true);
}

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

char **normalize_map(char **map, int rows, size_t cols)
{
    char **new_map = malloc(sizeof(char *) * rows);
    if (!new_map)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        // Allocate memory for the new row with +1 for null terminator
        new_map[i] = malloc(sizeof(char) * (cols + 2 + 1));
        if (!new_map[i])
        {
            // Free already allocated rows in case of failure
            for (int j = 0; j < i; j++)
                free(new_map[j]);
            free(new_map);
            return NULL;
        }

        // Add a leading space to the row
        new_map[i][0] = ' ';

        // Copy the original map row into the new row, starting after the leading space
        size_t len = ft_strlen(map[i]);
        ft_strlcpy(new_map[i] + 1, map[i], len + 1); // Copy at most cols - 1 characters

        // Pad with spaces if the original row is shorter than cols
        for (size_t j = len + 1; j < cols + 2; j++)
            new_map[i][j] = ' ';


        // Null-terminate the row
        new_map[i][cols + 2] = '\0';
    }

    return new_map;
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

void free_map(char **map, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
	}
	free(map);
}


// Main for testing
int main()
{
    char *map[] = {
        "111",
		"101",
		"S11",
    };

    t_player *player = malloc(sizeof(t_player));
    int rows = 3;
	if (!check_valid_chars(map, rows))
	{
		printf("Invalid characters in the map.\n");
		return (1);
	}
	

    if (!check_starting_pos(map, rows, player)) {
        printf("Invalid starting position.\n");
        return (1);
    }
	if (player->y == -1 || player->x == -1)
	{
		printf("No starting position found.\n");
		return (1);
	}
	
	printf("Player starting position: (%f, %f)\n", player->x, player->y);

    size_t cols = get_map_width(map, rows);
    printf("Map width: %zu\n", cols);
	char **new_map = normalize_map(map, rows, cols);
	
	for (int i = 0; i < rows; i++)
	{
		printf("the new map is %s\n", new_map[i]);
	}

	if (check_enclosure(new_map, rows, cols + 2) && check_top_and_bottom(new_map[0]) && check_top_and_bottom(new_map[rows - 1]))
        printf("The map is valid and enclosed!\n");
    else
        printf("The map is invalid (not properly enclosed)!\n");
    free(player);
	free_map(new_map, rows); // should properly free the new_map

    return 0;
}
