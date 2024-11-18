#include "cub3d.h"

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
}