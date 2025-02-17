/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:47:52 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/16 11:07:30 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

// Find the maximum row length
int	get_max_width(char **map)
{
	int	max_width;
	int	row_length;
	int	i;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		row_length = ft_strlen(map[i]);
		if (row_length > max_width)
			max_width = row_length;
		i++;
	}
	return (max_width);
}

// Check if a row is empty or contains only spaces
bool	is_empty_row(char *row)
{
	while (*row)
	{
		if (!ft_isspace(*row))
			return (false);
		row++;
	}
	return (true);
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	check_map_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ' && map[i][j] != '\n')
				handle_error("Invalid character in map");
			j++;
		}
		i++;
	}
}
