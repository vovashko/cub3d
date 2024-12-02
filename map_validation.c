/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 12:36:50 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/02 16:21:47 by vshkonda      ########   odam.nl         */
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



// Main for testing
int main()
{
    char *map[] = {
        "    111111       ",
        "11110000001N01111",
        "10000000101      ",
        "1111111111     00"
    };

    t_player *player = malloc(sizeof(t_player));
    int rows = 4;

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


    free(player);

    return 0;
}
