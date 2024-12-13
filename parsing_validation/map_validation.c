/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 12:36:50 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:25:32 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			{
				printf("Invalid character at (%d, %d): %c\n", i, j, map[i][j]);
				return (false);
			}
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



char **normalize_map(char **map, int rows, size_t cols)
{
    char **new_map = malloc(sizeof(char *) * rows);
    if (!new_map)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        // Allocate memory for the new row with +2 for null terminator
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


// Main for testing
bool map_check(t_map_file_data *mfd, t_player *player)
{
	if (!check_valid_chars(mfd->map, mfd->height))
	{
		printf("Invalid characters in the map.\n");
		return false;
	}

    if (!check_starting_pos(mfd->map, mfd->height, player)) {
        printf("Invalid starting position.\n");
        return false;
    }

    mfd->width = get_map_width(mfd->map, mfd->height);
    printf("Map width: %zu\n", mfd->width);
	char **new_map = normalize_map(mfd->map, mfd->height, mfd->width);
	
	for (int i = 0; i < mfd->height; i++)
	{
		printf("the new map is %s\n", new_map[i]);
	}

	if (check_enclosure(new_map, mfd->height, mfd->width + 2) && check_top_and_bottom(new_map[0]) && check_top_and_bottom(new_map[mfd->height - 1]))
        printf("The map is valid and enclosed!\n");
    else
        printf("The map is invalid (not properly enclosed)!\n");
    free(player);
	free_map(new_map, mfd->height); // should properly free the new_map

    return true;
}
