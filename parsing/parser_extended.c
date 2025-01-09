/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_extended.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:26:33 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/09 14:52:32 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	process_line(t_map_file_data *mfd, int *map_started, int fd, char *line)
{
	char	*trimmed_line;

	trimmed_line = skip_spaces(line);
	if (process_empty_line(*map_started, fd, line))
		return (true);
	if (is_config_line(trimmed_line) && !(*map_started))
		parse_config_line(mfd, trimmed_line);
	else if (ft_strchr("01NSEW", *trimmed_line))
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
