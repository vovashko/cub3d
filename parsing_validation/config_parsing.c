/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_parsing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 12:05:31 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:12:59 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_file_data(t_map_file_data *mfd, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		skip_spaces(line, &i);
		if (line[i] == 'N' && line[i + 1] == 'O')
			if (mfd->north_texture == NULL)
			{
				skip_spaces(line, &i);
				mfd->north_texture = ft_strdup(&line[i]);
			}
			else
				handle_error("Duplicate NO texture");
		else if (line[i] == 'S' && line[i + 1] == 'O')
			if (mfd->south_texture == NULL)
			{
				skip_spaces(line, &i);
				mfd->south_texture = ft_strdup(&line[i])
			}
			else
				handle_error("Duplicate SO texture");
		else if (line[i] == 'W' && line[i + 1] == 'E')
			if (mfd->west_texture == NULL)
			{
				skip_spaces(line, &i);
				mfd->west_texture = ft_strdup(&line[i])
			}			
			else
				handle_error("Duplicate WE texture");
		else if (line[i] == 'E' && line[i + 1] == 'A')
			if (mfd->east_texture == NULL)
			{
				skip_spaces(line, &i);
				mfd->east_texture = ft_strdup(&line[i])
			}
			else
				handle_error("Duplicate EA texture");
		else if (line[i] == 'F')
			if (mfd->floor_color->r == -1)
				get_color(&line[i + 2], mfd->floor_color);
			else
				handle_error("Duplicate color configuration");
		else if (line[i] == 'C')
		{
			if (mfd->ceiling_color->r == -1)
				get_color(&line[i + 2], mfd->ceiling_color);
			else
				handle_error("Duplicate color configuration");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}



bool	confirm_data_from_mfd(t_map_file_data *mfd)
{
	if (mfd->north_texture == NULL || mfd->south_texture == NULL
		|| mfd->west_texture == NULL || mfd->east_texture == NULL)
	{
		handle_error("Missing texture");
		return (false);
	}
	if (!check_color_range(mfd->floor_color))
	{
		handle_error("Invalid floor color");
		return (false);
	}
	if (!check_color_range(mfd->ceiling_color))
	{
		handle_error("Invalid ceiling color");
		return (false);
	}
	if (mfd->height == 0)
	{
		handle_error("Missing map");
		return (false);
	}
	return (true);
}



bool	check_file_content(t_map_file_data *mfd)
{
	int	fd;

	fd = open(mfd->file, O_RDONLY);
	if (fd == -1)
		return (false);
	get_file_data(mfd, fd);
	get_map_height(mfd);
	get_map(mfd);
	if (confirm_data_from_mfd(mfd) == false)
		return (false);
	return (true);
}

bool	check_file_format(char *file)
{
	int	i;

	i = ft_strlen(file) - 4; // to check the file extention which is 4 char long
	if (ft_strncmp(&file[i], ".cub", 4) != 0)
		return (false);
	return (true);
}