/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_file_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:49 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/30 14:58:41 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_file_format(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i
		- 4] != '.')
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
	color->g = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	color->b = ft_atoi(&line[i]);
}

void	get_map_height(t_map_file_data *mfd)
{
	char	*line;
	int		i;
	int		temp;

	temp = open(mfd->file, O_RDONLY);
	line = get_next_line(temp);
	while (line != NULL)
	{
		i = 0;
		skip_spaces(line, &i);
		if (line[i] == '1')
			mfd->height++;
		else if (line[i] != '1' && mfd->height > 0)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(temp);
	}
	while((line = get_next_line(temp)))
		free(line);
	close(temp);
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
	while ((line = get_next_line(fd)))
	{
		x = 0;	
		skip_spaces(line, &x);
		if (line[x] == '1')
			break ;
		free(line);
	}
	
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
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
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
			mfd->north_texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			mfd->south_texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			mfd->west_texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			mfd->east_texture = ft_strdup(&line[i + 2]);
		else if (line[i] == 'F')
			get_color(&line[i + 2], mfd->floor_color);
		else if (line[i] == 'C')
			get_color(&line[i + 2], mfd->ceiling_color);
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
	if (mfd->floor_color->r == -1 || mfd->floor_color->g == -1
		|| mfd->floor_color->b == -1)
	{
		handle_error("Missing floor color");
		return (false);
	}
	if (mfd->ceiling_color->r == -1 || mfd->ceiling_color->g == -1
		|| mfd->ceiling_color->b == -1)
	{
		handle_error("Missing ceiling color");
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

void	init_mfd(t_game *game, char *map_file)
{
	game->mfd = (t_map_file_data *)malloc(sizeof(t_map_file_data));
	game->mfd->file = map_file;
	game->mfd->width = 0;
	game->mfd->height = 0;
	game->mfd->floor_color = (t_color *)malloc(sizeof(t_color));
	game->mfd->floor_color->r = -1;
	game->mfd->floor_color->g = -1;
	game->mfd->floor_color->b = -1;
	game->mfd->ceiling_color = (t_color *)malloc(sizeof(t_color));
	game->mfd->ceiling_color->r = -1;
	game->mfd->ceiling_color->g = -1;
	game->mfd->ceiling_color->b = -1;
	game->mfd->north_texture = NULL;
	game->mfd->south_texture = NULL;
	game->mfd->west_texture = NULL;
	game->mfd->east_texture = NULL;
	game->mfd->map = NULL;
	if (check_file_content(game->mfd) == false)
	{
		handle_error("Invalid file content");
		free_mfd(game->mfd);
		exit(1);
	}
}
