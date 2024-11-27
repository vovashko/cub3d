/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2024/11/27 16:06:49 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "gnl/get_next_line.h"


#define PI 3.14159265359
#define WIDTH 800
#define HEIGHT 600
#define TEST_MODE 0

typedef struct s_ray
{
	int r; 	// ray number
	int mx; // map x
	int my; // map y
	int mp; // map position
	int dof; // direction of field
	float rx;   // ray x
	float ry;	// ray y
	float ra;   // ray angle
	float xo;	// x offset
	float yo;	// y offset
} t_ray;


typedef struct s_player
{
	mlx_image_t   *player_img;
	float x;
	float y;
	float dx;
	float dy;
	float dir;
	float fov;
} t_player;

typedef struct s_game
{
    void   *mlx;
    int*   map;
	mlx_image_t *background;
	mlx_image_t *wall;
	t_player *player;
	t_ray *ray;
} t_game;


void init_game(t_game *game, char *map_file);
void init_map(char *file, t_game *game);
bool check_file_format(char *file);
void key_hooks(void *params);
void update_player(void *params);
void draw_map(t_game *game);

#endif