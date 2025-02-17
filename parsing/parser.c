/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:22:56 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/15 16:45:41 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*check_and_assign_texture(char *texture, char *trimmed_line)
{
	if (texture == NULL)
		return (ft_strtrim(trimmed_line, " \t\n"));
	else
	{
		handle_error("Texture already exists and no duplicated are allowed");
		return (NULL);
	}
}

bool	process_line(t_map_file_data *mfd, int *map_started, char *line)
{
	char	*trimmed_line;

	trimmed_line = skip_spaces(line);
	if (!(*map_started) && trimmed_line[0] == '\n')
	{
		free(line);
		return (true);
	}
	if (is_config_line(trimmed_line) && !(*map_started))
		parse_config_line(mfd, trimmed_line);
	else if (ft_strchr("01NSEW\n", *trimmed_line))
	{
		if (!(*map_started))
			*map_started = 1;
		grow_map(mfd, trimmed_line);
	}
	else
	{
		free(line);
		return (handle_error("Invalid line encountered"), false);
	}
	free(line);
	return (true);
}

// Parses a configuration line for textures or colors
void	parse_config_line(t_map_file_data *mfd, char *line)
{
	char	*trimmed_line;

	trimmed_line = skip_spaces(line);
	if (ft_strncmp(trimmed_line, "NO", 2) == 0)
		mfd->north_texture = check_and_assign_texture(mfd->north_texture,
				skip_spaces(&trimmed_line[2]));
	else if (ft_strncmp(trimmed_line, "SO", 2) == 0)
		mfd->south_texture = check_and_assign_texture(mfd->south_texture,
				skip_spaces(&trimmed_line[2]));
	else if (ft_strncmp(trimmed_line, "WE", 2) == 0)
		mfd->west_texture = check_and_assign_texture(mfd->west_texture,
				skip_spaces(&trimmed_line[2]));
	else if (ft_strncmp(trimmed_line, "EA", 2) == 0)
		mfd->east_texture = check_and_assign_texture(mfd->east_texture,
				skip_spaces(&trimmed_line[2]));
	else if (ft_strncmp(trimmed_line, "F", 1) == 0)
		get_color(&trimmed_line[2], mfd->floor_color_config);
	else if (ft_strncmp(trimmed_line, "C", 1) == 0)
		get_color(&trimmed_line[2], mfd->ceiling_color_config);
	else
		handle_error("Invalid configuration line");
}

bool	get_file_data(t_map_file_data *mfd, int fd, int map_started)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (process_line(mfd, &map_started, line) == false)
			return (false);
		line = get_next_line(fd);
	}
	if (!map_started)
		return (handle_error("Map section not found"), false);
	return (true);
}
