/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:22:56 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/09 15:27:26 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*check_and_assign_texture(char *texture, char *trimmed_line)
{
	if (texture == NULL)
		return (trimmed_line);
	else
	{
		handle_error("Texture already exists and no duplicated are allowed");
		return (NULL);
	}
}

// Parses a configuration line for textures or colors
void	parse_config_line(t_map_file_data *mfd, char *line)
{
	char	*trimmed_line;

	trimmed_line = skip_spaces(line);
	if (ft_strncmp(trimmed_line, "NO", 2) == 0)
		mfd->north_texture = ft_strdup(check_and_assign_texture(\
		mfd->north_texture, skip_spaces(&trimmed_line[2])));
	else if (ft_strncmp(trimmed_line, "SO", 2) == 0)
		mfd->south_texture = ft_strdup(check_and_assign_texture(\
		mfd->south_texture, skip_spaces(&trimmed_line[2])));
	else if (ft_strncmp(trimmed_line, "WE", 2) == 0)
		mfd->west_texture = ft_strdup(check_and_assign_texture(\
		mfd->west_texture, skip_spaces(&trimmed_line[2])));
	else if (ft_strncmp(trimmed_line, "EA", 2) == 0)
		mfd->east_texture = ft_strdup(check_and_assign_texture(\
		mfd->east_texture, skip_spaces(&trimmed_line[2])));
	else if (ft_strncmp(trimmed_line, "F", 1) == 0)
		get_color(&trimmed_line[2], mfd->floor_color_config);
	else if (ft_strncmp(trimmed_line, "C", 1) == 0)
		get_color(&trimmed_line[2], mfd->ceiling_color_config);
	else
		handle_error("Invalid configuration line");
}

/*
	i'll the comment above the function.
	the commented line inside the function free(trimmed_line) 
	was causing the double free. If I understand it correctly I never copied
	data in to it, it just pointed to the same location and once line
	was freed there was no reason to free trimmed_line. That's my guess and now
	there's no issue when running cub3d with maps/bad/file_letter_end.cub
*/
static void	skip_empty_lines(int map_started, int fd)
{
	char	*line;
	char	*trimmed_line;

	if (map_started)
	{
		line = get_next_line(fd);
		if (line)
			trimmed_line = skip_spaces(line);
		if (line && trimmed_line && ft_strlen(trimmed_line) == 1 \
		&& trimmed_line[0] == '\n')
		{
			free(line);
			// free(trimmed_line);
			handle_error("Empty lines found in map section\n");
		}
		free(line);
	}
}

bool	process_empty_line(int map_started, int fd, char *line)
{
	if (*line == '\n')
	{
		skip_empty_lines(map_started, fd);
		free(line);
		return (true);
	}
	return (false);
}

//TODO: think how to fix the error that commes up.
// the thing is that in a while loop statement we can't do
// line = get_next_line(fd)
// we need to do it in a different way because of the norm. the 
// issue that arises
// is that when we process an empty line, we free it and continue, 
// but then it doesn't grab a new line and we fail

bool	get_file_data(t_map_file_data *mfd, int fd, int map_started)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (process_line(mfd, &map_started, fd, line) == false)
			return (false);
		line = get_next_line(fd);
	}
	if (!map_started)
		return (handle_error("Map section not found"), false);
	return (true);
}
