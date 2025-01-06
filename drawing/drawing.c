/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:06:20 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/06 12:44:22 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update_player(void *params)
{
	t_game *game = (t_game *)params;
	if (mlx_image_to_window(game->mlx, game->player->player_img, game->player->x, game->player->y) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
}

void draw_map(t_game *game)
{
	int x = 0;
	int y = 0;
	int i = 0;
	while (y < 10)
	{
		while (x < 10)
		{
			if (game->map[i] == 1)
			{
				if (mlx_image_to_window(game->mlx, game->wall, x * TILE_SIZE, y * TILE_SIZE) == -1)
				{
					printf("Error\nFailed to draw image\n");
					exit(1);
				}
			}
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}
