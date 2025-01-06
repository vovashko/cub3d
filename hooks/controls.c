/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:03:16 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/06 13:08:16 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void turn_controls(t_game *game)
{
    double old_dx;
    double old_plane_x;
    double turn = 0.1; // Rotation angle

    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        turn = -turn; // Rotate left
    }
    else if (!mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        return; // No rotation
    }

    old_dx = game->player->dx;
    old_plane_x = game->player->plane_x;

    // Rotate direction vector
    game->player->dx = game->player->dx * cos(turn) - game->player->dy * sin(turn);
    game->player->dy = old_dx * sin(turn) + game->player->dy * cos(turn);

    // Rotate camera plane
    game->player->plane_x = game->player->plane_x * cos(turn) - game->player->plane_y * sin(turn);
    game->player->plane_y = old_plane_x * sin(turn) + game->player->plane_y * cos(turn);
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
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x -= game->player->dy;
		game->player->y += game->player->dx;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x += game->player->dy;
		game->player->y -= game->player->dx;
	}
	turn_controls(game);
	
}
