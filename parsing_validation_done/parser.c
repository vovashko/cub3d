#include "../cub3d.h"

static char *check_and_assign_texture(char *texture, char *trimmed_line)
{
    if (texture == NULL)
        return (trimmed_line);
    else
    {
        handle_error("Texture already exists and no duplicated are allowed");
        return NULL;
    }
}

// Parses a configuration line for textures or colors
void parse_config_line(t_map_file_data *mfd, char *line)
{
    // Trim leading spaces
    char *trimmed_line = skip_spaces(line);

    if (ft_strncmp(trimmed_line, "NO ", 3) == 0) // North texture
        mfd->north_texture = ft_strdup(check_and_assign_texture(mfd->north_texture, skip_spaces(&trimmed_line[3])));
    else if (ft_strncmp(trimmed_line, "SO ", 3) == 0) // South texture
        mfd->south_texture = ft_strdup(check_and_assign_texture(mfd->south_texture, skip_spaces(&trimmed_line[3])));
    else if (ft_strncmp(trimmed_line, "WE ", 3) == 0) // West texture
        mfd->west_texture = ft_strdup(check_and_assign_texture(mfd->west_texture, skip_spaces(&trimmed_line[3])));
    else if (ft_strncmp(trimmed_line, "EA ", 3) == 0) // East texture
        mfd->east_texture = ft_strdup(check_and_assign_texture(mfd->east_texture, skip_spaces(&trimmed_line[3])));
    else if (ft_strncmp(trimmed_line, "F ", 2) == 0) // Floor color
        get_color(&trimmed_line[2], mfd->floor_color);
    else if (ft_strncmp(trimmed_line, "C ", 2) == 0) // Ceiling color
        get_color(&trimmed_line[2], mfd->ceiling_color);
    else
        handle_error("Invalid configuration line");
}

static void skip_empty_lines(int map_started, int fd)
{
    char *line;
    char *trimmed_line;

    if (map_started)
    {
        line = get_next_line(fd);
        if (line)
            trimmed_line = skip_spaces(line);
        if (line && trimmed_line && !ft_strchr(trimmed_line, '\n'))
        {
            free(line);
            free(trimmed_line);
            handle_error("Empty lines found in map section\n");
        }
    }
    
}

static bool process_empty_line(int map_started, int fd, char *line)
{
    if (*line == '\n')
    {
        skip_empty_lines(map_started, fd);
        free(line);
        return true;
    }
    return false;
}

bool get_file_data(t_map_file_data *mfd, int fd)
{
    char *line;
    int map_started;
    char *trimmed_line;

    map_started = 0;
    while ((line = get_next_line(fd)))
    {
        trimmed_line = skip_spaces(line);
        if (process_empty_line(map_started, fd, line))
            continue;
        if (is_config_line(trimmed_line) && !map_started)
            parse_config_line(mfd, trimmed_line); // Parse texture/color line
        else if (ft_strchr("01NSEW", *trimmed_line))
        {
            if (!map_started)
                map_started = 1;
            grow_map(mfd, trimmed_line); // Add the line to the map
        }
        else
            return (handle_error("Invalid line encountered"), false);
        free(line);
    }
    if (!map_started)
        return (handle_error("Map section not found"), false);
    return true;
}
