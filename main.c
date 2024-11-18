#include "cub3d.h"



void init_game(t_game *game)
{
    game->win_w = 640;
    game->win_h = 480;
    game->mlx = mlx_init(game->win_w, game->win_h, "cub3d", true);
    
}

void key_hooks(void *params)
{
    t_game *game = (t_game *)params;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        printf("Player walks forwards\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        printf("Player walks backwards\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
        printf("Player walks left\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
        printf("Player walks right\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        printf("Player turns left\n");
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        printf("Player turns right\n");
        
}


bool check_file_format(char *file)
{
    int i;

    i = 0;
    while (file[i] != '\0')
        i++;
    if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
        return (false);
    return (true);
}


int main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\nInvalid number of arguments\n");
        return (1);
    }

    if (check_file_format(argv[1]) == false)
    {
        printf("Error\nInvalid file format\nPlease provide a file with the .cub extension\n");
        return (1);
    }

    t_game game;
    init_game(&game);
    mlx_loop_hook(game.mlx, &key_hooks, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    
}