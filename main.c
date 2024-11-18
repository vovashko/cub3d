#include "cub3d.h"



void init_game(t_game *game)
{
    game->win_w = 640;
    game->win_h = 480;
    game->mlx = mlx_init(game->win_w, game->win_h, "cub3d", true);
    game->res_x = 100;
    game->res_y = 100;
    game->img = NULL;
    
}

uint32_t random_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void randomizer(void *params)
{
    uint32_t i;
    uint32_t j;
    uint32_t color;
    t_game *game = (t_game *)params;

    i = 0;
    while (i < game->img->width)
    {
        j = 0;
        while (j < game->img->height)
        {
            color = random_color(rand() % 255, rand() % 255, rand() % 255, 255);
            mlx_put_pixel(game->img, i, j, color);
            j++;
        }
        i++;
    }


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


    if (!(game.img = mlx_new_image(game.mlx, 100, 100)))
    {
        printf("Error\nFailed to create image\n");
        return (1);
    }

    if (mlx_image_to_window(game.mlx, game.img, 0, 0) == false)
    {
        printf("Error\nFailed to draw image\n");
        return (1);
    }

    
    mlx_loop_hook(game.mlx, &randomizer, &game);
    mlx_loop_hook(game.mlx, &key_hooks, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    
}