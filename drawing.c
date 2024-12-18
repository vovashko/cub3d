/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:06:20 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/18 13:41:49 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


void draw_floor_and_ceiling(t_game *game)
{
	int x;
	int y;
	int floor_color;
	int ceiling_color;
	

	floor_color = get_rgba(39, 245, 236, 255);
	ceiling_color = get_rgba(245, 121, 3, 255);

	x = 0;
	
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->background, x, y, ceiling_color);
			y++;
		}
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->background, x, y, floor_color);
			y++;
		}
		x++;
	}
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
