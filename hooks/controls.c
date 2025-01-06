/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:03:16 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/06 14:45:08 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	turn_controls(t_game *game)
{
	double	old_dx;
	double	old_plane_x;

	double turn = 0.1; // Rotation angle
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		turn = -turn; // Rotate left
	}
	else if (!mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		return ; // No rotation
	}
	old_dx = game->player->dx;
	old_plane_x = game->player->plane_x;
	// Rotate direction vector
	game->player->dx = game->player->dx * cos(turn) - game->player->dy
		* sin(turn);
	game->player->dy = old_dx * sin(turn) + game->player->dy * cos(turn);
	// Rotate camera plane
	game->player->plane_x = game->player->plane_x * cos(turn)
		- game->player->plane_y * sin(turn);
	game->player->plane_y = old_plane_x * sin(turn) + game->player->plane_y
		* cos(turn);
}

void	check_wall_collission(t_player *player, char **map, float target_x, float target_y)
{
	
	if (map[(int)player->y][(int)target_x] == '0')
		player->x = target_x;
	if (map[(int)target_y][(int)player->x] == '0')
		player->y = target_y;
}

void player_movement(t_player *player, char key, char **map)
{
	float	target_x;
	float	target_y;

	if (key == 'W')
	{
		target_x = player->x + player->dx;
		target_y = player->y + player->dy;
	}
	if (key == 'S')
	{
		target_x = player->x - player->dx;
		target_y = player->y - player->dy;
	}
	if (key == 'A')
	{
		target_x = player->x + player->dy;
		target_y = player->y - player->dx;
	}
	if (key == 'D')
	{
		target_x = player->x - player->dy;
		target_y = player->y + player->dx;
	}
	check_wall_collission(player, map, target_x, target_y);
}



void	key_hooks(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player_movement(game->player, 'W', game->mfd->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player_movement(game->player, 'S', game->mfd->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player_movement(game->player, 'D', game->mfd->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		player_movement(game->player, 'A', game->mfd->map);
	turn_controls(game);
}

void	update_player(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (mlx_image_to_window(game->mlx, game->player->player_img,
			game->player->x, game->player->y) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
}
