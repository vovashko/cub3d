/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:55:22 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/08 13:22:34 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_player_position(char **map, int x, int y, t_player *player)
{
	if (ft_strchr("SWEN", map[y][x]))
	{
		player->x = x + 0.5;
		player->y = y + 0.5;
		player->dir = map[y][x];
		map[y][x] = '0';
		return (1);
	}
	return (0);
}

// Validate player presence
bool	validate_player_presence(char **map, t_player *player)
{
	int	player_count;
	int	y;
	int	x;

	player_count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			player_count += check_player_position(map, x, y, player);
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		handle_error("Invalid number of starting positions");
		return (false);
	}
	return (true);
}

// Validate file content
bool	check_file_content(t_map_file_data *mfd)
{
	if (!mfd->north_texture || !mfd->south_texture || \
	!mfd->west_texture || !mfd->east_texture || \
	!mfd->floor_color || !mfd->ceiling_color)
		handle_error("Missing essential map data");
	if (open(ft_strtrim(mfd->south_texture, " \t\n"), O_RDONLY) == -1)
		handle_error("Could not open north texture file");
	if (open(ft_strtrim(mfd->south_texture, " \t\n"), O_RDONLY) == -1)
	 	handle_error("Could not open south texture file");
	if (open(ft_strtrim(mfd->west_texture, " \t\n"), O_RDONLY) == -1)
	 	handle_error("Could not west south texture file");
	if (open(ft_strtrim(mfd->east_texture, " \t\n"), O_RDONLY) == -1)
	 	handle_error("Could not open east texture file");
	return (true);
}

// Wrapper to validate the entire map
bool	validate_map(t_map_file_data *mfd, t_player *player)
{
	if (!check_file_content(mfd))
		return (false);
	if (!check_colours_range(mfd->ceiling_color) || \
		!check_colours_range(mfd->floor_color))
		return (false);
	if (!validate_map_enclosure(mfd->map))
		return (false);
	if (!validate_player_presence(mfd->map, player))
		return (false);
	return (true);
}
