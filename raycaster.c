#include "cub3d.h"

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

int	perform_dda(t_ray *ray, int *map)
{
	int	hor;

	hor = 0;
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
		// Check if the ray hits a wall
		if (get_map_value(map, ray->hit_x, ray->hit_y) == 1)
			return (hor);
	}
}

void	calculate_wall_height(t_ray *ray, int hor, t_player *player)
{
	if (hor == 0)
		ray->hit_distance = (ray->hit_y - player->y + (1 - ray->step_dir_y) / 2) / ray->dy;
	else
		ray->hit_distance = (ray->hit_x - player->x + (1 - ray->step_dir_x) / 2) / ray->dx;

	if (ray->hit_distance < 0)
		ray->hit_distance = 1e30;
	if	(hor == 0)
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




uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_textured_color(int x, int y, mlx_texture_t *texture)
{
	uint32_t base_color;

	int32_t r;
	int32_t g;
	int32_t b;
	int32_t a;

	r = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	g = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel + 1];
	b = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel + 2];
	a = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel + 3];

	base_color = get_rgba(r, g, b, a);

	return (base_color);
}

mlx_texture_t *assign_texture(t_ray *ray)
{
	mlx_texture_t *texture;

	switch (ray->hit_orientation)
	{
	case 'N':
		texture = ray->walls->north;
		break;
	case 'S':
		texture = ray->walls->south;
		break;
	case 'E':
		texture = ray->walls->east;
		break;
	case 'W':
		texture = ray->walls->west;
		break;
	default:
		texture = ray->walls->north;
		break;
	}
	return (texture);
}

void	draw_wall_slice(t_game *game, t_ray *ray)
{
	
	int	i;

	int floor_color = get_rgba(245, 121, 3, 255); // Orange
	int ceiling_color = get_rgba(39, 245, 236, 255);  // Cyan
	int texture_x;
	int texture_y;
	double scale;
	double tex_pos;
	mlx_texture_t *current_texture;


	current_texture = assign_texture(ray);
	texture_x = (ray->hit_portion * current_texture->width);
	scale = (double)current_texture->height / ray->slice_height;
	tex_pos = (ray->wall_start - HEIGHT / 2 + ray->slice_height / 2) * scale;
	i = 0;
	// Draw ceiling
	for (i = 0; i < ray->wall_start; i++)
		mlx_put_pixel(game->background, ray->slice, i, ceiling_color);
	// Draw wall
	for (i = ray->wall_start; i <= ray->wall_end; i++)
	{
		texture_y = (int)tex_pos % (current_texture->height);
		tex_pos += scale;
		mlx_put_pixel(game->background, ray->slice, i, get_textured_color(texture_x, texture_y, current_texture));
	}
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

	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
		// stretch image based on window size changing
	mlx_loop_hook(game->mlx, game_loop, game);
	// mlx_cursor_hook(game->mlx, mouse_turn, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}