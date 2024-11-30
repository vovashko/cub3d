/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_file_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:49 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/30 13:21:45 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool check_file_format(char *file)
{
    int i;

    i = 0;
    while (file[i] != '\0')
        i++;
    if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
        return (false);
    return (true);
}
void	handle_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

void	get_color(char *line, t_color *color)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	color->r = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	printf("line after r %s\n", &line[i]);
	color->g = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	printf("line after g %s\n", &line[i]);
	color->b = ft_atoi(&line[i]);
}


void	get_map_height(t_map_file_data *mfd)
{
	char	*line;
	int		i;
	int temp;

	temp = open(mfd->file, O_RDONLY);

	line = get_next_line(temp);
	while (line != NULL)
	{
		i = 0;
		skip_spaces(line, &i);
		if (line[i] == '1')
			mfd->height++;
		else if (line[i] != '1' && mfd->height > 0)
			break;
		line = get_next_line(temp);
	}
	close(temp);
}

// void	get_map_width(t_map_file_data *mfd)
// {
// 	char	*line;
// 	int		i;
// 	int		width;

// 	fd = open(mfd->file, O_RDONLY);
	

// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		width = 0;
// 		i = 0;
// 		while (line[i] != '\n' && line[i] != '\0')
// 		{
// 			width++;
// 			i++;
// 		}
// 		if (width > mfd->width)
// 			mfd->width = width;
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }

void	get_map(t_map_file_data *mfd)
{
	int		fd;
	int		y;
	char	*line;

	get_map_height(mfd);
	mfd->map = (char **)malloc(sizeof(char *) * mfd->height + 1);
	y = 0;
	fd = open(mfd->file, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open file");
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '1')
			break;
		free(line);
	}
	while (y < mfd->height)
	{
		
		printf("the line is %s\n", line);
		if (line == NULL)
			handle_error("Invalid map");
		mfd->map[y] = ft_strdup(line);
		if (mfd->map[y] == NULL)
			handle_error("Failed to allocate memory");
		free(line);
		line = get_next_line(fd);
		y++;
	}
	mfd->map[y] = NULL;
	close(fd);
}

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
			mfd->north_texture = &line[i + 2];
		else if (line[i] == 'S' && line[i + 1] == 'O')
			mfd->south_texture = &line[i + 2];
		else if (line[i] == 'W' && line[i + 1] == 'E')
			mfd->west_texture = &line[i + 2];
		else if (line[i] == 'E' && line[i + 1] == 'A')
			mfd->east_texture = &line[i + 2];
		else if (line[i] == 'F')
			get_color(&line[i + 2], mfd->floor_color);
		else if (line[i] == 'C')
			get_color(&line[i + 2], mfd->ceiling_color);
		line = get_next_line(fd);
	}
	close(fd);
}

bool	check_file_content(t_map_file_data *mfd)
{
	int	fd;
	// char c;

	fd = open(mfd->file, O_RDONLY);
	if (fd == -1)
		return (false);
	// check if the file is empty
	// if (read(fd, &c, 1) <= 0)
	// {
	// 	close(fd);
	// 	return (false);
	// }
	get_file_data(mfd, fd);
	get_map(mfd);
	return (true);
}

void	init_mfd(t_game *game, char *map_file)
{
	game->mfd = (t_map_file_data *)malloc(sizeof(t_map_file_data));
	game->mfd->file = map_file;
	game->mfd->width = 0;
	game->mfd->height = 0;
	game->mfd->floor_color = (t_color *)malloc(sizeof(t_color));
	game->mfd->ceiling_color = (t_color *)malloc(sizeof(t_color));
	game->mfd->north_texture = NULL;
	game->mfd->south_texture = NULL;
	game->mfd->west_texture = NULL;
	game->mfd->east_texture = NULL;
	game->mfd->map = NULL;
	if (check_file_content(game->mfd) == false)
		handle_error("Invalid file content");
}