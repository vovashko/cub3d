/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/08 15:06:55 by vshkonda      #+#    #+#                 */
/*   Updated: 2025/01/15 16:56:27 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_start_dir(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dx = 0;
		player->dy = -1;
	}
	else if (player->dir == 'S')
	{
		player->dx = 0;
		player->dy = 1;
	}
	else if (player->dir == 'W')
	{
		player->dx = -1;
		player->dy = 0;
	}
	else if (player->dir == 'E')
	{
		player->dx = 1;
		player->dy = 0;
	}
}

void	update_plane_start_dir(t_player *player)
{
	if (player->dir == 'N')
	{
		player->plane_x = FOV_SCALE;
		player->plane_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->plane_x = -FOV_SCALE;
		player->plane_y = 0;
	}
	else if (player->dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -FOV_SCALE;
	}
	else if (player->dir == 'E')
	{
		player->plane_x = 0;
		player->plane_y = FOV_SCALE;
	}
}

void	handle_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(EXIT_FAILURE);
}

bool	check_file_format(char *file)
{
	int	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(&file[i], ".cub", 4) != 0)
		return (false);
	return (true);
}
