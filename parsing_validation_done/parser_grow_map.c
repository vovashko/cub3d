/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_grow_map.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:13:26 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/02 10:16:06 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_map(t_map_file_data *mfd, char *line)
{
	mfd->map = malloc(sizeof(char *) * 2);
	if (!mfd->map)
		handle_error("Failed to allocate memory for map");
	mfd->map[0] = ft_strdup(line);
	if (!mfd->map[0])
		handle_error("Failed to duplicate map line");
	mfd->map[1] = NULL;
	mfd->height = 1;
}

void	grow_map(t_map_file_data *mfd, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	if (mfd->map == NULL)
	{
		initialize_map(mfd, line);
		return ;
	}
	new_map = malloc(sizeof(char *) * (mfd->height + 2));
	if (!new_map)
		handle_error("Failed to allocate memory for growing map");
	while (i < mfd->height)
	{
		new_map[i] = mfd->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
		handle_error("Failed to duplicate map line");
	new_map[++i] = NULL;
	free(mfd->map);
	mfd->map = new_map;
	mfd->height++;
}
