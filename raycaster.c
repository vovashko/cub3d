/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/11 17:02:18 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

void perform_dda (t_ray *ray, int *map)
{
	while (ray->dof < MAX_DOF)
		{
			ray->map_x = (int)(ray->x) / TILE_SIZE;
			ray->map_y = (int)(ray->y) / TILE_SIZE;
			ray->map_pos = ray->map_y * MAP_WIDTH + ray->map_x; // instead of 10, use the actual map width
			if (ray->map_pos >= 0 && ray->map_pos < 100 && map[ray->map_pos] == 1) // instead of 100, use the actual map size
				ray->dof = MAX_DOF;
			else
			{
				ray->x += ray->x_offset;
				ray->y += ray->y_offset;
				ray->dof += 1;
			}
		}	
}



void check_horizontal(t_ray *ray, t_player *player, int *map)
{
		ray->dof = 0;
		float aTan = -1 / tan(ray->dir);
		if (ray->dir > PI) // ray facing down
		{
			ray->y = (((int)player->y / TILE_SIZE) * TILE_SIZE) - EPSILON;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = -TILE_SIZE;
			ray->x_offset = ray->y_offset * aTan;
		}
		else if (ray->dir < PI) // ray facing up
		{
			ray->y = (((int)player->y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = TILE_SIZE;
			ray->x_offset = ray->y_offset * aTan;
		}
		else // ray facing right or left
		{
			ray->x = player->x;
			ray->y = player->y;
			ray->dof = MAX_DOF;
		}
		perform_dda(ray, map);
}

void check_vertical(t_ray *ray, t_player *player, int *map)
{
		ray->dof = 0;
		float nTan = -tan(ray->dir);
		if (ray->dir > PI_2 && ray->dir < (PI + PI_2)) // ray facing left
		{
			ray->x = (((int)player->x / TILE_SIZE) * TILE_SIZE) - EPSILON;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = -TILE_SIZE;
			ray->y_offset = ray->x_offset * nTan;
		}
		else if (ray->dir < PI_2 || ray->dir > (PI + PI_2)) // ray facing right
		{
			ray->x = (((int)player->x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = TILE_SIZE;
			ray->y_offset = ray->x_offset * nTan;
		}
		else  // ray facing up or dwon
		{
			ray->x = player->x;
			ray->y = player->y;
			ray->dof = MAX_DOF;
		}
		perform_dda(ray, map);
		
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