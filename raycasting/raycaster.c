/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/08 15:35:53 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * ray->slice / (double)WIDTH - 1;
	ray->dx = player->dx + player->plane_x * ray->camera_x;
	ray->dy = player->dy + player->plane_y * ray->camera_x;
	ray->hit_x = (int)player->x;
	ray->hit_y = (int)player->y;
	if (ray->dy == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dy);
	if (ray->dx == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dx);
	assign_starting_dist(ray, player);
}

void	assign_starting_dist(t_ray *ray, t_player *player)
{
	if (ray->dx < 0)
	{
		ray->step_dir_x = -1;
		ray->dist_x = (player->x - ray->hit_x) * ray->delta_x;
	}
	else
	{
		ray->step_dir_x = 1;
		ray->dist_x = (ray->hit_x + 1.0 - player->x) * ray->delta_x;
	}
	if (ray->dy < 0)
	{
		ray->step_dir_y = -1;
		ray->dist_y = (player->y - ray->hit_y) * ray->delta_y;
	}
	else
	{
		ray->step_dir_y = 1;
		ray->dist_y = (ray->hit_y + 1.0 - player->y) * ray->delta_y;
	}
}

int	perform_dda(t_ray *ray, char **map, int hor)
{
	while (1)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->hit_x += ray->step_dir_x;
			hor = 1;
			if (ray->step_dir_x > 0)
				ray->hit_orientation = 'E';
			else
				ray->hit_orientation = 'W';
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->hit_y += ray->step_dir_y;
			hor = 0;
			if (ray->step_dir_y > 0)
				ray->hit_orientation = 'S';
			else
				ray->hit_orientation = 'N';
		}
		if (map[ray->hit_y][ray->hit_x] == '1')
			return (hor);
	}
}

void	calculate_wall_height(t_ray *ray, int hor, t_player *player)
{
	if (hor == 0)
		ray->hit_distance = (ray->hit_y - player->y + (1 - ray->step_dir_y) / 2)
			/ ray->dy;
	else
		ray->hit_distance = (ray->hit_x - player->x + (1 - ray->step_dir_x) / 2)
			/ ray->dx;
	if (ray->hit_distance < 0)
		ray->hit_distance = 1e30;
	if (hor == 0)
		ray->hit_portion = player->x + ray->hit_distance * ray->dx;
	else
		ray->hit_portion = player->y + ray->hit_distance * ray->dy;
	ray->hit_portion -= floor(ray->hit_portion);
	if (ray->hit_orientation == 'W' || ray->hit_orientation == 'S')
		ray->hit_portion = 1 - ray->hit_portion;
	ray->slice_height = (int)(HEIGHT / ray->hit_distance);
	ray->wall_start = HEIGHT / 2 - ray->slice_height / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->slice_height / 2 + HEIGHT / 2;
	if (ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT - 1;
}

void	raycast_and_render(t_game *game)
{
	int				hor;
	mlx_texture_t	*current_texture;

	game->ray->slice = 0;
	while (game->ray->slice < WIDTH)
	{
		init_ray(game->ray, game->player);
		hor = perform_dda(game->ray, game->mfd->map, 0);
		calculate_wall_height(game->ray, hor, game->player);
		current_texture = assign_texture(game->ray);
		draw_wall_slice(game, game->ray, current_texture);
		game->ray->slice++;
	}
}
