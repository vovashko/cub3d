/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2024/11/25 15:00:26 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

#define PI 3.14159265359
#define WIDTH 800
#define HEIGHT 600


typedef struct s_player
{
	mlx_image_t   *player_img;
	int x;
	int y;
	int dir;
} t_player;

typedef struct s_game
{
    void   *mlx;
    int*   map;
	mlx_image_t *background;
	t_player *player;
} t_game;


void init_game(t_game *game);
bool check_file_format(char *file);

#endif