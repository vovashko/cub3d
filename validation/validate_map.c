/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:42:28 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/15 12:17:51 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_rows(char **map, int *i, \
char **row_on_top, char **row_on_bottom)
{
	*row_on_top = NULL;
	*row_on_bottom = NULL;
	if (*i > 0)
		*row_on_top = map[*i - 1];
	if (map[*i + 1])
		*row_on_bottom = map[*i + 1];
}

static bool	validate_edge_rows(char *curr_row, \
char *row_on_top, char *row_on_bottom, int i)
{
	if (i == 0 && !validate_edge_gaps(curr_row, row_on_bottom))
		return (false);
	if (!row_on_bottom && !validate_edge_gaps(curr_row, row_on_top))
		return (false);
	return (true);
}

static bool	handle_row_validation(char *curr_row, \
char *row_on_top, char *row_on_bottom)
{
	if (!is_row_enclosed(curr_row))
		return (false);
	if (row_on_top && row_on_bottom && \
		!validate_middle_row_gaps(curr_row, row_on_top, row_on_bottom))
		return (false);
	return (true);
}

static bool	process_empty_rows(char *curr_row, int *empty_row_detected)
{
	if (is_empty_row(curr_row))
	{
		*empty_row_detected = 1;
		return (true);
	}
	if (*empty_row_detected)
	{
		handle_error("Map contains floating or disconnected rows.");
		return (false);
	}
	return (true);
}

// Validate map enclosure
bool	validate_map_enclosure(char **map)
{
	static int	i;
	int			empty_row_detected;
	char		*row_on_top;
	char		*row_on_bottom;

	empty_row_detected = 0;
	if (!map || !map[0])
		return (handle_error("Map is missing or empty."), false);
	while (map[i])
	{
		initialize_rows(map, &i, &row_on_top, &row_on_bottom);
		if (!process_empty_rows(map[i], &empty_row_detected))
			return (false);
		if (is_empty_row(map[i]))
		{
			i++;
			continue ;
		}
		if (!validate_edge_rows(map[i], row_on_top, row_on_bottom, i))
			return (false);
		if (i >= 1 && !handle_row_validation(map[i], row_on_top, row_on_bottom))
			return (false);
		i++;
	}
	return (true);
}
