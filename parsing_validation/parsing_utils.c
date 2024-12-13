/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 12:03:28 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:41:02 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void free_map(char **map, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
	}
	free(map);
}