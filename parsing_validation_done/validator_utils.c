/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:47:52 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/02 10:52:12 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r')
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
