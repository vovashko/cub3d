/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:49 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:16:56 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *skip_to_map(int fd)
{
    char *line;
    int i;

    while ((line = get_next_line(fd)) != NULL)
    {
        i = 0;
        // Skip leading spaces
        while (line[i] == ' ')
            i++;

        // Check if the line is part of the configuration or empty
        if (line[i] == '\n' ||
            (line[i] == 'N' && line[i + 1] == 'O') ||
            (line[i] == 'S' && line[i + 1] == 'O') ||
            (line[i] == 'W' && line[i + 1] == 'E') ||
            (line[i] == 'E' && line[i + 1] == 'A') ||
            (line[i] == 'F') ||
            (line[i] == 'C'))
        {
            free(line);
            continue;
        }

        // Return the first valid map line
        return line;
    }

    return NULL; // Return NULL if no valid map line is found
}

size_t get_map_width(char **map, int rows)
{
	int y;
	size_t current_len;

	y = 0;
	size_t width = 0;
	
	while (y < rows)
	{
		printf("the map is %s\n", map[y]);
		current_len = ft_strlen(map[y]);
		if (current_len > width)
			width = current_len;
		y++;
	}
	return (width);
}

void get_map_height(t_map_file_data *mfd)
{
    char *line;
    int temp;

    temp = open(mfd->file, O_RDONLY);
    if (temp == -1)
        handle_error("Failed to open file");

    // Skip to the map section
    line = skip_to_map(temp);

    // Count map lines
    while (line != NULL)
    {
        if (line[0] == '\n')
			break ;
		mfd->height++;
        free(line);
        line = get_next_line(temp);
		
    }

    close(temp);

    if (mfd->height == 0)
        handle_error("No valid map found in file");
}



void	get_map(t_map_file_data *mfd)
{
	int		fd;
	int		y;
	int		x;
	char	*line;

	mfd->map = (char **)malloc(sizeof(char *) * mfd->height);
	if (mfd->map == NULL)
		handle_error("Failed to allocate memory");
	y = 0;
	x = 0;
	fd = open(mfd->file, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open file");
	line = skip_to_map(fd);
	while (y < mfd->height && line != NULL)
	{
		x = 0;
		skip_spaces(line, &x);
		if (line[x] == '\0' || line[x] == '\n')
		{
			free(line);
			break ;
		}
		mfd->map[y] = ft_strdup(line);
		if (mfd->map[y] == NULL)
			handle_error("Failed to allocate memory");
		mfd->map[y][ft_strlen(line) - 1] = '\0';
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}


