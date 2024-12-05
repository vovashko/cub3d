/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2024/12/05 16:13:58 by vshkonda      ########   odam.nl         */
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
# include "libft/libft/libft.h"


#define PI 3.14159265359
#define PI_2 1.57079632679  
#define FOV 60
#define TILE_SIZE 64
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_SIZE 100
#define PLAYER_SIZE 50
#define ONE_DEGREE 0.01745329251

#define WIDTH 800
#define HEIGHT 600
#define TEST_MODE 2
#define MAX_DOF 8

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_map_file_data
{
	char *file;
	size_t width;
	int height;
	t_color *floor_color;
	t_color *ceiling_color;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char **map;
} t_map_file_data;


typedef struct s_ray
{
	int ray_num; 	// ray number
	int map_x; // map x
	int map_y; // map y
	int map_pos; // map position
	int dof; // direction of field
	float x;   // ray x
	float y;	// ray y
	float dir;   // ray angle
	float x_offset;	// x offset
	float y_offset;	// y offset
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
    t_map_file_data *mfd;
	mlx_image_t *background;
	mlx_image_t *wall;
	t_player *player;
	t_ray *ray;
} t_game;


void init_game(t_game *game, char *map_file);
void init_mfd(t_game *game, char *file);
bool check_file_format(char *file);
void key_hooks(void *params);
void update_player(void *params);
void draw_map(t_game *game);
void free_mfd(t_map_file_data *mfd);
bool map_check(t_map_file_data *mfd, t_player *player);

#endif