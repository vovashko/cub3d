/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:03:16 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/27 16:05:29 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void turn_controls(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        {
			game->player->dir -= 0.1;
			if (game->player->dir < 0)
				game->player->dir += 2 * PI;
			game->player->dx = cos(game->player->dir) * 5;
			game->player->dy = sin(game->player->dir) * 5;
		}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		{
			game->player->dir += 0.1;
			if (game->player->dir > 2 * PI)
				game->player->dir -= 2 * PI;
			game->player->dx = cos(game->player->dir) * 5;
			game->player->dy = sin(game->player->dir) * 5;
		}
}

void key_hooks(void *params)
{
    t_game *game = (t_game *)params;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->y += game->player->dy;
		game->player->x += game->player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->y -= game->player->dy;
		game->player->x -= game->player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x -= 5;
		game->player->y += 5;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x += game->player->dx;
		game->player->y -= game->player->dy;
	}
	turn_controls(game);
}
