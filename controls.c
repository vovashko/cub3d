/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:03:16 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/03 16:41:44 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render(void *param);

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


// this function is called when the mouse wheel is scrolled
void mouse_turn(double delta_x, double delta_y, void *param)
{
	t_game *game = (t_game *)param;
	(void)delta_y;

	double old_dx;
    double old_plane_x;
    double turn = 0.1; // Rotation angle
	old_dx = game->player->dx;
    old_plane_x = game->player->plane_x;

	if (delta_x < 0)
	{
		turn = -turn; // Rotate left
	}
	else if (delta_x == 0)
	{
		return; // No rotation
	}

    // Rotate direction vector
    game->player->dx = game->player->dx * cos(turn) - game->player->dy * sin(turn);
    game->player->dy = old_dx * sin(turn) + game->player->dy * cos(turn);

    // Rotate camera plane
    game->player->plane_x = game->player->plane_x * cos(turn) - game->player->plane_y * sin(turn);
    game->player->plane_y = old_plane_x * sin(turn) + game->player->plane_y * cos(turn);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		mouse_turn(1, 0, game);
	turn_controls(game);
}
