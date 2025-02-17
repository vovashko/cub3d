/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 16:03:16 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/16 11:12:12 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	turn_controls(t_game *game)
{
	double	old_dx;
	double	old_plane_x;
	double	rotation_angle;

	rotation_angle = ROTATION_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotation_angle = -rotation_angle;
	else if (!mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		return ;
	old_dx = game->player->dx;
	old_plane_x = game->player->plane_x;
	game->player->dx = game->player->dx * cos(rotation_angle) - game->player->dy
		* sin(rotation_angle);
	game->player->dy = old_dx * sin(rotation_angle) + game->player->dy
		* cos(rotation_angle);
	game->player->plane_x = game->player->plane_x * cos(rotation_angle)
		- game->player->plane_y * sin(rotation_angle);
	game->player->plane_y = old_plane_x * sin(rotation_angle)
		+ game->player->plane_y * cos(rotation_angle);
}

void	check_wall_collission(t_player *player, char **map, float target_x,
		float target_y)
{
	if (map[(int)player->y][(int)target_x] == '0')
		player->x = target_x;
	if (map[(int)target_y][(int)player->x] == '0')
		player->y = target_y;
}

void	player_movement(t_player *player, char key, char **map)
{
	float	target_x;
	float	target_y;

	if (key == 'W')
	{
		target_x = player->x + player->dx * SPEED;
		target_y = player->y + player->dy * SPEED;
	}
	if (key == 'S')
	{
		target_x = player->x - player->dx * SPEED;
		target_y = player->y - player->dy * SPEED;
	}
	if (key == 'A')
	{
		target_x = player->x + player->dy * SPEED;
		target_y = player->y - player->dx * SPEED;
	}
	if (key == 'D')
	{
		target_x = player->x - player->dy * SPEED;
		target_y = player->y + player->dx * SPEED;
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
		handle_error("Failed to draw player image");
}
