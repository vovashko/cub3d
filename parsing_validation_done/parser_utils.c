#include "../cub3d.h"

void handle_error(char *error)
{
    fprintf(stderr, "Error: %s\n", error);
    exit(EXIT_FAILURE);
}

char *skip_spaces(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return line;
}

// Skips lines until it reaches the map section
char *skip_to_map(int fd)
{
    char *line;

    while ((line = get_next_line(fd)))
    {
        int i = 0;
        skip_spaces(line);
        if (is_config_line(line))
        {
            free(line);
            continue;
        }
        if (ft_strchr("01NSEW", line[i]))
            return line;
        free(line);
    }
    return NULL;
}

void get_map_height(t_map_file_data *mfd, int fd)
{
    int height = 0;
    char *line;

    if (fd < 0)
        handle_error("Error opening file to determine map height");

    line = skip_to_map(fd);

    while ((line = get_next_line(fd)))
    {
        if (ft_strlen(line) > 0)
            height++;
        free(line);
    }
    close(fd);
    mfd->height = height;
}

bool is_config_line(const char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0 ||
        ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 ||
        ft_strncmp(line, "EA ", 3) == 0 ||
        ft_strncmp(line, "F ", 2) == 0 ||
        ft_strncmp(line, "C ", 2) == 0)
        return true;
    return false;
}