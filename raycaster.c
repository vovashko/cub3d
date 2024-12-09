/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/09 16:06:50 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"


void check_horizontal(t_ray *ray, t_player *player, int *map)
{
		ray->dof = 0;
		float aTan = -1 / tan(ray->dir);
		if (ray->dir > PI) // ray facing down
		{
			ray->y = (((int)player->y >> 6) << 6) - 0.0001;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = -64;
			ray->x_offset = ray->y_offset * aTan;
		}
		else if (ray->dir < PI) // ray facing up
		{
			ray->y = (((int)player->y >> 6) << 6) + 64;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = 64;
			ray->x_offset = ray->y_offset * aTan;
		}
		else // ray facing right or left
		{
			ray->x = player->x;
			ray->y = player->y;
			ray->dof = MAX_DOF;
		}
		while (ray->dof < MAX_DOF)
		{
			ray->map_x = (int)(ray->x) >> 6;
			ray->map_y = (int)(ray->y) >> 6;
			ray->map_pos = ray->map_y * MAP_WIDTH  + ray->map_x; // instead of 10, use the actual map width
			if (ray->map_pos > 0 && map[ray->map_pos] == 1) // instead of 100, use the actual map size
				ray->dof = MAX_DOF;
			else
			{
				ray->x += ray->x_offset;
				ray->y += ray->y_offset;
				ray->dof += 1;
			}
		}
}

void check_vertical(t_ray *ray, t_player *player, int *map)
{
		ray->dof = 0;
		float nTan = -tan(ray->dir);
		if (ray->dir > PI_2 && ray->dir < (PI + PI_2)) // ray facing left
		{
			ray->x = (((int)player->x >> 6) << 6) - 0.0001;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = -64;
			ray->y_offset = ray->x_offset * nTan;
		}
		else if (ray->dir < PI_2 || ray->dir > (PI + PI_2)) // ray facing right
		{
			ray->x = (((int)player->x >> 6) << 6) + 64;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = 64;
			ray->y_offset = ray->x_offset * nTan;
		}
		else  // ray facing up or dwon
		{
			ray->x = player->x;
			ray->y = player->y;
			ray->dof = MAX_DOF;
		}
		while (ray->dof < MAX_DOF)
		{
			ray->map_x = (int)(ray->x) >> 6;
			ray->map_y = (int)(ray->y) >> 6;
			ray->map_pos = ray->map_y * MAP_HEIGHT + ray->map_x; // instead of 10, use the actual map height
			if (ray->map_pos > 0 && ray->map_pos < 100 && map[ray->map_pos] == 1) // instead of 100, use the actual map size
				ray->dof = MAX_DOF;
			else
			{
				ray->x += ray->x_offset;
				ray->y += ray->y_offset;
				ray->dof += 1;
			}
		}	
}

float shortest_distance(t_ray *ray, t_player *player)
{
	float h_dist = sqrt((ray->x - player->x) * (ray->x - player->x) + (ray->y - player->y) * (ray->y - player->y));
	float v_dist = sqrt((ray->x - player->x) * (ray->x - player->x) + (ray->y - player->y) * (ray->y - player->y));
	if (h_dist < v_dist)
		return (h_dist);
	else
		return (v_dist);
}

void draw_walls(t_player *player, t_ray *ray)
{
	float distance = shortest_distance(ray, player);
	float angle = player->dir - ray->dir;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	distance *= cos(angle);
	float wall_height = (TILE_SIZE / distance) * 277;
	if (wall_height > 277)
		wall_height = 277;
	// float wall_strip_x = ray->ray_num * TILE_SIZE;
	// float wall_strip_y = (HEIGHT - wall_height) / 2;
	
}

void raycaster(t_player *player, t_ray *ray, int *map)
{
	
	check_horizontal(ray, player, map);
	check_vertical(ray, player, map);
	draw_walls(player, ray);
	
}


int main()
{

	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");
	
	
	draw_map(game);
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	raycaster(game->player, game->ray, game->map);
	return (0);
}