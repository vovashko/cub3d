/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:29 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/16 11:45:28 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	mlx_delete_texture(game->ray->walls->north);
	mlx_delete_texture(game->ray->walls->south);
	mlx_delete_texture(game->ray->walls->west);
	mlx_delete_texture(game->ray->walls->east);
	free(game->ray->walls);
	free(game->ray);
	free_mfd(game->mfd);
	free_player(game->player);
	free(game);
}

void	free_mfd(t_map_file_data *mfd)
{
	int	i;

	i = 0;
	while (i < mfd->height)
	{
		free(mfd->map[i]);
		i++;
	}
	free(mfd->map);
	free(mfd->north_texture);
	free(mfd->south_texture);
	free(mfd->west_texture);
	free(mfd->east_texture);
	free(mfd->floor_color_config);
	free(mfd->ceiling_color_config);
	free(mfd);
}

void	free_player(t_player *player)
{
	free(player);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	key_hooks(game);
	update_player(game);
	raycast_and_render(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2 || !check_file_format(argv[1]))
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (EXIT_FAILURE);
	}
	game = (t_game *)malloc(sizeof(t_game));
	init_game(game, argv[1]);
	if (!validate_map(game->mfd, game->player))
	{
		handle_error("Invalid map");
	}
	init_graphics(game);
	init_ray_struct(game->ray, game->mfd);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
