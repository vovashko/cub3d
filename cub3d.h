/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2024/12/13 16:21:43 by vshkonda      ########   odam.nl         */
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
#define RAD 0.01745329251
#define EPSILON 0.0001

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


typedef struct s_ray {
    int ray_num;         // Ray number
    int map_x;           // Map grid x-coordinate
    int map_y;           // Map grid y-coordinate
    int map_pos;         // Map array position
    int dof;             // Depth of field
    int hit;             // 1 if a wall is hit, 0 otherwise
    int hit_orientation; // 0 for horizontal, 1 for vertical
    float x;             // Current ray x-coordinate
    float y;             // Current ray y-coordinate
    float h_x;           // Horizontal hit x-coordinate
    float h_y;           // Horizontal hit y-coordinate
    float v_x;           // Vertical hit x-coordinate
    float v_y;           // Vertical hit y-coordinate
    float dir;           // Ray angle
    float x_offset;      // Offset for stepping x
    float y_offset;      // Offset for stepping y
    float h_dist;        // Distance to horizontal hit
    float v_dist;        // Distance to vertical hit
    float texture_offset; // Offset for texturing
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
	int *map;   // remove after testing
} t_game;


void init_game(t_game *game, char *map_file);
void init_mfd(t_game *game, char *file);
bool check_file_format(char *file);
void key_hooks(void *params);
void update_player(void *params);
void draw_map(t_game *game);
void free_mfd(t_map_file_data *mfd);
bool map_check(t_map_file_data *mfd, t_player *player);
void skip_spaces(char *line, int *i);
void handle_error(char *error);
void free_map(char **map, int rows);
void get_file_data(t_map_file_data *mfd, int fd);
void get_map_height(t_map_file_data *mfd);
void get_map(t_map_file_data *mfd);
bool check_file_content(t_map_file_data *mfd);
void get_color(char *line, t_color *color);
int verify_color(char *line, int *i);
bool check_color_range(t_color *color);
bool confirm_data_from_mfd(t_map_file_data *mfd);
char *skip_to_map(int fd);
size_t get_map_width(char **map, int rows);
char **normalize_map(char **map, int rows, size_t cols);
bool check_enclosure(char **map, int rows, size_t cols);
bool is_surrounded_by_walls_or_spaces(char **map, size_t x, int y, int rows, size_t cols);
bool check_top_and_bottom(char *line);
bool check_valid_chars(char **map, int rows);
bool check_starting_pos(char **map, int rows, t_player *player);




#endif