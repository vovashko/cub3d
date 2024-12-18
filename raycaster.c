/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/18 15:18:20 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

void find_wall(t_ray *ray, int *map)
{
		int dof = 0;
		while (dof < MAX_DOF)
		{
			ray->map_x = (int)(ray->x) >> 6;
			ray->map_y = (int)(ray->y) >> 6;
			ray->map_pos = ray->map_y * MAP_WIDTH  + ray->map_x; // instead of 10, use the actual map width
			if (ray->map_pos > 0 && ray->map_pos < 10 * 10 && map[ray->map_pos] == 1) // instead of 100, use the actual map size
				break ;
			else
			{
				ray->x += ray->x_offset;
				ray->y += ray->y_offset;
				dof += 1;
			}
		}
}

void check_horizontal(t_ray *ray, t_player *player, int *map)
{
		float aTan = -1 / tan(ray->dir);
		if (ray->dir > PI) // ray facing down
		{
			ray->y = (((int)player->y >> 6) << 6) - 0.0001;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = -64;
			ray->x_offset = -ray->y_offset * aTan;
		}
		else if (ray->dir < PI) // ray facing up
		{
			ray->y = (((int)player->y >> 6) << 6) + 64;
			ray->x = (player->y - ray->y) * aTan + player->x;
			ray->y_offset = 64;
			ray->x_offset = -ray->y_offset * aTan;
		}
		else // ray facing right or left
		{
			ray->x = player->x;
			ray->y = player->y;
			return ;
		}
		find_wall(ray, map);
}

void check_vertical(t_ray *ray, t_player *player, int *map)
{
		float nTan = -tan(ray->dir);
		if (ray->dir > PI_2 && ray->dir < (PI + PI_2)) // ray facing left
		{
			ray->x = (((int)player->x >> 6) << 6) - 0.0001;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = -64;
			ray->y_offset = -ray->x_offset * nTan;
		}
		else if (ray->dir < PI_2 || ray->dir > (PI + PI_2)) // ray facing right
		{
			ray->x = (((int)player->x >> 6) << 6) + 64;
			ray->y = (player->x - ray->x) * nTan + player->y;
			ray->x_offset = 64;
			ray->y_offset = -ray->x_offset * nTan;
		}
		else  // ray facing up or dwon
		{
			ray->x = player->x;
			ray->y = player->y;
			return ;
		}
		find_wall(ray, map);
}

void hit_distance(t_ray *ray, t_player *player, int *map)
{
	check_horizontal(ray, player, map);
	float h_dist = sqrt(pow((ray->x - player->x),2) + pow((ray->y - player->y), 2));
	check_vertical(ray, player, map);
	float v_dist = sqrt(pow((ray->x - player->x),2) + pow((ray->y - player->y), 2));
	if (h_dist < v_dist)
		ray->hit_distance = h_dist;
	else
		ray->hit_distance = v_dist;
}

void draw_walls(t_ray *ray, t_game *game)
{
	float line_height = (TILE_SIZE / ray->hit_distance) * WIDTH;
	float draw_start = HEIGHT / 2 - line_height / 2;
	float draw_end = HEIGHT / 2 + line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	int color = get_rgba(25, 21, 73, 15);
;
	int x = ray->ray_num;
	int y = draw_start;
	while (y < draw_end)
	{
		mlx_put_pixel(game->wall, x, y, color);
		y++;
	}
	
}

void calculate_ray(t_ray *ray, int ray_num)
{
	ray->dir = ray->dir - RAD * FOV / 2 + RAD * FOV / WIDTH * ray_num;
	if (ray->dir < 0)
		ray->dir += 2 * PI;
	if (ray->dir > 2 * PI)
		ray->dir -= 2 * PI;	
}

void raycaster(t_player *player, t_ray *ray, int *map, t_game *game)
{
	int ray_num = 0;
	ray->dir = player->dir - RAD * FOV / 2 + RAD * FOV / WIDTH * ray_num;
	while(ray_num < WIDTH)
	{
		calculate_ray(ray, ray_num);
		hit_distance(ray, player, map);
		draw_walls(ray, game);
		ray_num++;
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

void render(void *params)
{
	t_game *game = (t_game *)params;
	raycaster(game->player, game->ray, game->map, game);
}

int main()
{

	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");
	
	
	draw_floor_and_ceiling(game);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->wall, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);    // stretch image based on window size changing
	mlx_loop_hook(game->mlx, key_hooks, game);
	mlx_loop_hook(game->mlx, update_player, game);
	mlx_loop_hook(game->mlx, render, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
	
	return (0);
}