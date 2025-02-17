/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/06 12:46:19 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/16 12:09:51 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*assign_texture(t_ray *ray)
{
	mlx_texture_t	*texture;

	if (ray->hit_orientation == 'N')
		texture = ray->walls->north;
	else if (ray->hit_orientation == 'S')
		texture = ray->walls->south;
	else if (ray->hit_orientation == 'W')
		texture = ray->walls->west;
	else
		texture = ray->walls->east;
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

void	draw_wall_slice(t_game *game, t_ray *ray,
		mlx_texture_t *current_texture)
{
	int		i;
	int		texture_x;
	int		texture_y;
	double	scale;
	double	tex_pos;

	texture_x = fmin(fmax(ray->hit_portion * current_texture->width, 0), \
	current_texture->width - 1);
	scale = (double)current_texture->height / ray->slice_height;
	tex_pos = (ray->wall_start - HEIGHT / 2 + ray->slice_height / 2) * scale;
	i = 0;
	while (i < ray->wall_start)
		mlx_put_pixel(game->background, ray->slice, i++, game->ceiling_color);
	while (i <= ray->wall_end)
	{
		texture_y = (int)tex_pos % (current_texture->height);
		tex_pos += scale;
		mlx_put_pixel(game->background, ray->slice, i++,
			get_textured_color(texture_x, texture_y, current_texture));
	}
	while (i < HEIGHT)
		mlx_put_pixel(game->background, ray->slice, i++, game->floor_color);
}
