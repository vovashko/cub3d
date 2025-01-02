#include "cub3d.h"

void	init_ray(t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * ray->slice / (double)WIDTH - 1;
	ray->x = player->dx + player->plane_x * ray->camera_x;
	ray->y = player->dy + player->plane_y * ray->camera_x;
	ray->hit_x = (int)player->x;
	ray->hit_y = (int)player->y;

	if (ray->y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->y);
	if (ray->x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->x);
	
	if (ray->x < 0)
	{
		ray->x_dir = -1;
		ray->dist_x = (player->x - ray->hit_x) * ray->delta_x;
	}
	else
	{
		ray->x_dir = 1;
		ray->dist_x = (ray->hit_x + 1.0 - player->x) * ray->delta_x;
	}
	if (ray->y < 0)
	{
		ray->y_dir = -1;
		ray->dist_y = (player->y - ray->hit_y) * ray->delta_y;
	}
	else
	{
		ray->y_dir = 1;
		ray->dist_y = (ray->hit_y + 1.0 - player->y) * ray->delta_y;
	}
}

int	perform_dda(t_ray *ray, int *map)
{
	int	hor;

	hor = 0;
	while (1)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->hit_x += ray->x_dir;
			hor = 1;
			if (ray->x_dir > 0)
				ray->hit_orientation = 'N';
			else
				ray->hit_orientation = 'S';
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->hit_y += ray->y_dir;
			hor = 0;
			if (ray->y_dir > 0)
				ray->hit_orientation = 'W';
			else
				ray->hit_orientation = 'E';
		}
		// Check if the ray hits a wall
		if (get_map_value(map, ray->hit_x, ray->hit_y) == 1)
			return (hor);
	}
}

void	calculate_wall_height(t_ray *ray, int hor, t_player *player)
{
	if (hor == 0)
		ray->hit_distance = (ray->hit_y - player->y + (1 - ray->y_dir) / 2) / ray->y;
	else
		ray->hit_distance = (ray->hit_x - player->x + (1 - ray->x_dir) / 2) / ray->x;

	if (ray->hit_distance < 0)
		ray->hit_distance = 1e30;

	ray->slice_height = (int)(HEIGHT / ray->hit_distance);
	ray->wall_start = HEIGHT / 2 - ray->slice_height / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->slice_height / 2 + HEIGHT / 2;
	if (ray->wall_end >= HEIGHT)
	{
		ray->wall_end = HEIGHT - 1;
	}
}




int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_textured_color(char orientation)
{
	int	base_color;

	// Example: Blend the wall orientation color with texture coordinates
	switch (orientation)
	{
	case 'N':
		base_color = get_rgba(255, 0, 0, 255);
		break ; // Red for north
	case 'S':
		base_color = get_rgba(0, 255, 0, 255);
		break ; // Green for south
	case 'E':
		base_color = get_rgba(0, 0, 255, 255);
		break ; // Blue for east
	case 'W':
		base_color = get_rgba(255, 255, 0, 255);
		break ; // Yellow for west
	default:
		base_color = get_rgba(255, 255, 255, 255);
		break ; // White fallback
	}
	return (base_color);
}

void	draw_wall_slice(t_game *game, t_ray *ray)
{
	int	wall_color;
	int	i;

	int ceiling_color = get_rgba(245, 121, 3, 255); // Orange
	int floor_color = get_rgba(39, 245, 236, 255);  // Cyan
	wall_color = get_textured_color(ray->hit_orientation);
	i = 0;
	// Draw ceiling
	for (i = 0; i < ray->wall_start; i++)
		mlx_put_pixel(game->background, ray->slice, i, ceiling_color);
	// Draw wall
	for (i = ray->wall_start; i <= ray->wall_end; i++)
		mlx_put_pixel(game->background, ray->slice, i, wall_color);
	// Draw floor
	for (i = ray->wall_end + 1; i < HEIGHT; i++)
		mlx_put_pixel(game->background, ray->slice, i, floor_color);
}

int	get_map_value(int *map, int x, int y)
{
	return (map[y * 10 + x]); // Assuming map width is 10
}







void	raycast_and_render(t_game *game)
{
	int	hor;

	game->ray->slice = 0;
	// reset_window(game->background);
	while (game->ray->slice < WIDTH)
	{
		init_ray(game->ray, game->player);
		hor = perform_dda(game->ray, game->map);
		calculate_wall_height(game->ray, hor, game->player);
		draw_wall_slice(game, game->ray);
		game->ray->slice++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	key_hooks(game);
	update_player(game);
	raycast_and_render(game);
}

int	main(void)
{
	t_game *game = (t_game *)malloc(sizeof(t_game));
	init_game(game, "map.cub");

	// draw_floor_and_ceiling(game);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
		// stretch image based on window size changing
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}