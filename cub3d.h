/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2025/01/16 12:13:02 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "gnl/get_next_line.h"
# include "libft/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64
# define WIDTH 1200
# define HEIGHT 800
# define FOV_SCALE 0.75
# define ROTATION_SPEED 0.02
# define SPEED 0.02

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_map_file_data
{
	char			*file;
	size_t			width;
	int				height;
	t_color			*floor_color_config;
	t_color			*ceiling_color_config;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			**map;
}					t_map_file_data;

typedef struct s_walls
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}					t_walls;

/*
	int slice;              // Ray slice (column)
	float dx;               // Ray x direction
	float dy;               // Ray y direction
	float delta_x;          // Step size in x-direction
	float delta_y;          // Step size in y-direction
	float dist_x;           // Distance to next x gridline
	float dist_y;           // Distance to next y gridline
	int hit_x;              // Map x position of wall hit
	int hit_y;              // Map y position of wall hit
	int step_dir_x;         // Direction of step in x (-1 or 1)
	int step_dir_y;         // Direction of step in y (-1 or 1)
	double hit_distance;    // Final distance to the wall hit
	float hit_portion;      // Texture alignment
	char hit_orientation;   // Orientation of the wall hit
	u_int32_t slice_height; // Height of the wall slice
	u_int32_t texture_x;    // Texture x coordinate
	double camera_x;        // Camera x coordinate
	int wall_start;         // Start of the wall slice
	int wall_end;           // End of the wall slice
	t_walls			*walls;
*/

typedef struct s_ray
{
	int				slice;
	float			dx;
	float			dy;
	float			delta_x;
	float			delta_y;
	float			dist_x;
	float			dist_y;
	int				hit_x;
	int				hit_y;
	int				step_dir_x;
	int				step_dir_y;
	double			hit_distance;
	float			hit_portion;
	char			hit_orientation;
	u_int32_t		slice_height;
	u_int32_t		texture_x;
	double			camera_x;
	int				wall_start;
	int				wall_end;
	t_walls			*walls;
}					t_ray;

typedef struct s_player
{
	mlx_image_t		*player_img;
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			plane_x;
	float			plane_y;
	char			dir;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	t_map_file_data	*mfd;
	mlx_image_t		*background;
	mlx_image_t		*wall;
	t_player		*player;
	t_ray			*ray;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}					t_game;

void				init_game(t_game *game, char *map_file);
void				init_graphics(t_game *game);
bool				check_file_format(char *file);
void				key_hooks(void *params);
void				update_player(void *params);
void				draw_map(t_game *game);
void				free_mfd(t_map_file_data *mfd);
void				free_player(t_player *player);
void				handle_error(char *error);
void				free_map(char **map, int rows);
void				get_map(t_map_file_data *mfd);
bool				check_file_content(t_map_file_data *mfd);
void				get_color(char *line, t_color *color);
int					verify_color(char *line, int *i);
bool				confirm_data_from_mfd(t_map_file_data *mfd);
char				*skip_to_map(int fd);
size_t				get_map_width(char **map, int rows);
bool				check_enclosure(char **map, int rows, size_t cols);
bool				check_top_and_bottom(char *line);
bool				check_valid_chars(char **map, int rows);
void				draw_floor_and_ceiling(t_game *game);
void				draw_wall_slice(t_game *game, t_ray *ray,
						mlx_texture_t *current_texture);

void				handle_error(char *error);
char				*skip_spaces(char *line);
void				parse_config_line(t_map_file_data *mfd, char *line);
bool				ft_isspace(char c);
int					get_max_width(char **map);
bool				is_empty_row(char *row);
bool				is_row_enclosed(char *row);
bool				validate_edge_gaps(char *curr_row, char *adjacent_row);
bool				validate_middle_row_gaps(char *curr_row, char *row_on_top,
						char *row_on_bottom);
bool				validate_player_presence(char **map, t_player *player);
bool				validate_map_enclosure(char **map);
bool				check_file_content(t_map_file_data *mfd);
bool				check_colours_range(t_color *color);
bool				validate_map(t_map_file_data *mfd, t_player *player);
void				get_map_height(t_map_file_data *mfd, int fd);
bool				get_file_data(t_map_file_data *mfd, int fd,
						int map_started);
bool				process_line(t_map_file_data *mfd, int *map_started,
						char *line);
bool				is_config_line(const char *line);
void				grow_map(t_map_file_data *mfd, char *line);
void				check_map_chars(char **map);

void				raycast_and_render(t_game *game);
uint32_t			get_rgba(int r, int g, int b, int a);
char				get_map_value(char **map, int x, int y);
mlx_texture_t		*assign_texture(t_ray *ray);
uint32_t			get_textured_color(int x, int y, mlx_texture_t *texture);
void				convert_floor_and_ceiling_colors(t_game *game);
void				update_player_start_dir(t_player *player);
void				update_plane_start_dir(t_player *player);
void				assign_starting_dist(t_ray *ray, t_player *player);
void				init_ray_struct(t_ray *ray, t_map_file_data *mfd);

#endif