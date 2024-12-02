/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 12:36:50 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/02 17:12:48 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// - add map validation: 
// 	- need to be transform like in flood fill?
// 	- one starting player position based on which side player is facing (N,S,W,E)
// 	- no unexpected chars
// 	- map should be fully encircled by the walls, no newlines


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
	for (int i = 0; i < rows; i++)
	{
		new_map[i] = malloc(sizeof(char) * cols + 1);
		new_map[i][0] = ' ';
		new_map[i] = ft_strjoin(new_map[i], map[i]);
		if (ft_strlen(new_map[i]) < cols + 1)
		{
			size_t j = ft_strlen(new_map[i]);
			while (j < cols)
			{
				new_map[i][j] = ' ';
				j++;
			}
			new_map[i][j] = '\0';
		}
	}
	return new_map;
}

// Main for testing
int main()
{
    char *map[] = {
        "    111111111",
        "11110000001111111",
        "100000100111",
        "11111111111S"
    };

    t_player *player = malloc(sizeof(t_player));
    int rows = 4;
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

	if (check_enclosure(new_map, rows, cols))
        printf("The map is valid and enclosed!\n");
    else
        printf("The map is invalid (not properly enclosed)!\n");
    free(player);
	free(new_map);

    return 0;
}
