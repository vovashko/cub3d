/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:21 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/10 12:52:09 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->player_img = mlx_new_image(game->mlx, 1, 1);
	if (game->player->player_img == NULL)
	{
		printf("Error\nFailed to create player image\n");
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->player->player_img, 0, 0) == -1)
	{
		printf("Error\nFailed to draw image\n");
		exit(1);
	}
	game->player->player_img->enabled = false;
	game->player->x = -1;
	game->player->y = -1;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->player->dx = 1;
	game->player->dy = 0;
}

void	init_mfd(t_game *game, int fd)
{
	game->mfd = (t_map_file_data *)malloc(sizeof(t_map_file_data));
	game->mfd->width = 0;
	game->mfd->height = 0;
	game->mfd->floor_color_config = (t_color *)malloc(sizeof(t_color));
	game->mfd->floor_color_config->r = -1;
	game->mfd->floor_color_config->g = -1;
	game->mfd->floor_color_config->b = -1;
	game->mfd->ceiling_color_config = (t_color *)malloc(sizeof(t_color));
	game->mfd->ceiling_color_config->r = -1;
	game->mfd->ceiling_color_config->g = -1;
	game->mfd->ceiling_color_config->b = -1;
	game->mfd->north_texture = NULL;
	game->mfd->south_texture = NULL;
	game->mfd->west_texture = NULL;
	game->mfd->east_texture = NULL;
	game->mfd->map = NULL;
	if (get_file_data(game->mfd, fd, 0) == false)
		handle_error("Invalid file content");
}

void	init_ray_struct(t_ray *ray, t_map_file_data *mfd)
{
	ray->slice = 0;
	ray->dx = 0;
	ray->dy = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->dist_x = 0;
	ray->dist_y = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->step_dir_x = 0;
	ray->step_dir_y = 0;
	ray->hit_portion = 0;
	ray->walls = (t_walls *)malloc(sizeof(t_walls));
	printf("north_texture: |%s|\n", mfd->north_texture);
	ray->walls->north = mlx_load_png(mfd->north_texture);
	ray->walls->south = mlx_load_png(mfd->south_texture);
	ray->walls->west = mlx_load_png(mfd->west_texture);
	ray->walls->east = mlx_load_png(mfd->east_texture);
	(void)mfd;
}

void	init_game(t_game *game, char *map_file)
{
	t_ray	*ray;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open map file");
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) == -1)
		handle_error("Failed to draw background");
	init_player(game);
	init_mfd(game, fd);
	convert_floor_and_ceiling_colors(game);
	ray = (t_ray *)malloc(sizeof(t_ray));
	game->ray = ray;
	init_ray_struct(game->ray, game->mfd);
}
