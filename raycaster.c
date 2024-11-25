/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 17:23:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/25 17:39:49 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycaster(t_game *game)
{
	check_horizontal(game->ray, game);
	check_vertical(game->ray, game);
}

void check_horizontal(t_ray *ray, t_game *game)
{
	ray->ra = game->player->dir;
	for (r = 0,; r < 1; r++)
	{
		ray->dof = 0;
		float aTan = -1 / tan(ray->ra);
		if (ray->ra > PI) // ray facing down
		{
			ray->ry = (((int)game->player->y >> 6) << 6) - 0.0001;
			ray->rx = (game->player->y - ray->ry) * aTan + game->player->x;
			ray->yo = -64;
			ray->xo = -ray->yo * aTan;
		}
		if (ray->ra < PI) // ray facing up
		{
			ray->ry = (((int)game->player->y >> 6) << 6) + 64;
			ray->rx = (game->player->y - ray->ry) * aTan + game->player->x;
			ray->yo = 64;
			ray->xo = -ray->yo * aTan;
		}
		if (ray->ra == 0 || ray->ra == PI) // ray facing right or left
		{
			ray->rx = game->player->x;
			ray->ry = game->player->y;
			ray->dof = 8;
		}
		while (ray->dof < 8)
		{
			ray->mx = (int)(ray->rx) >> 6;
			ray->my = (int)(ray->ry) >> 6;
			ray->mp = ray->my * 10 + ray->mx;
			if (ray->mp > 0 && ray->mp < 100 && game->map[ray->mp] == 1)
			{
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->dof = 8;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof += 1;
			}
		}
	}	
}

void check_vertical(t_game *game)
{
	ray->ra = game->player->dir;
	for (r = 0,; r < 1; r++)
	{
		ray->dof = 0;
		float nTan = -tan(ray->ra);
		if (ray->ra > PI / 2 && ray->ra < 1.5 * PI) // ray facing left
		{
			ray->rx = (((int)game->player->x >> 6) << 6) - 0.0001;
			ray->ry = (game->player->x - ray->rx) * nTan + game->player->y;
			ray->xo = -64;
			ray->yo = -ray->xo * nTan;
		}
		if (ray->ra < PI / 2 || ray->ra > 1.5 * PI) // ray facing right
		{
			ray->rx = (((int)game->player->x >> 6) << 6) + 64;
			ray->ry = (game->player->x - ray->rx) * nTan + game->player->y;
			ray->xo = 64;
			ray->yo = -ray->xo * nTan;
		}
		if (ray->ra == 0 || ray->ra == PI) // ray facing right or left
		{
			ray->rx = game->player->x;
			ray->ry = game->player->y;
			ray->dof = 8;
		}
		while (ray->dof < 8)
		{
			ray->mx = (int)(ray->rx) >> 6;
			ray->my = (int)(ray->ry) >> 6;
			ray->mp = ray->my * 10 + ray->mx;
			if (ray->mp > 0 && ray->mp < 100 && game->map[ray->mp] == 1)
			{
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->dof = 8;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof += 1;
			}
		}
	}	
}