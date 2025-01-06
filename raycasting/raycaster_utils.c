/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/06 12:46:19 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/06 15:04:40 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	get_map_value(char **map, int x, int y)
{
	return (map[y][x]);
}

mlx_texture_t	*assign_texture(t_ray *ray)
{
	mlx_texture_t	*texture;

	switch (ray->hit_orientation)
	{
	case 'N':
		texture = ray->walls->north;
		break ;
	case 'S':
		texture = ray->walls->south;
		break ;
	case 'E':
		texture = ray->walls->east;
		break ;
	case 'W':
		texture = ray->walls->west;
		break ;
	default:
		texture = ray->walls->north;
		break ;
	}
	return (texture);
}

void	convert_floor_and_ceiling_colors(t_game *game)
{
	game->floor_color = get_rgba(game->mfd->floor_color_config->r,
			game->mfd->floor_color_config->g, game->mfd->floor_color_config->b,
			255);
	game->ceiling_color = get_rgba(game->mfd->ceiling_color_config->r,
			game->mfd->ceiling_color_config->g,
			game->mfd->ceiling_color_config->b, 255);
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_textured_color(int x, int y, mlx_texture_t *texture)
{
	uint32_t	base_color;
	int32_t		r;
	int32_t		g;
	int32_t		b;
	int32_t		a;

	r = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	g = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel
		+ 1];
	b = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel
		+ 2];
	a = texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel
		+ 3];
	base_color = get_rgba(r, g, b, a);
	return (base_color);
}
