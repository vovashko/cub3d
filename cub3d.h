/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vovashko <vovashko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:33:40 by vovashko      #+#    #+#                 */
/*   Updated: 2024/11/18 16:37:30 by vovashko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_game
{
    void   *mlx;
    int    win_w;
    int    win_h;
    int    res_x;
    int    res_y;
    void   *img;
    
} t_game;

#endif