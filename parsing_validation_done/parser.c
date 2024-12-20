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

// Checks if the line contains a texture or color prefix
static bool is_config_line(const char *line)
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

// Skips lines until it reaches the map section
char *skip_to_map(int fd)
{
    char *line;

    while ((line = get_next_line(fd)))
    {
        int i = 0;
        skip_spaces(line);

        // Check for configuration lines and skip them
        if (is_config_line(line))
        {
            free(line);
            continue;
        }

        // If the line starts with '0', '1', or player positions, return it
        if (ft_strchr("01NSEW", line[i]))
            return line;

        // Free other invalid lines
        free(line);
    }
    return NULL; // No map found
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
        if (ft_strlen(line) > 0) // Count only non-empty lines
            height++;
        free(line);
    }
    close(fd);
    mfd->height = height;
}

void free_mfd(t_map_file_data *mfd)
{
    if (mfd->map)
        free_map(mfd->map, mfd->height);
    free(mfd->floor_color);
    free(mfd->ceiling_color);
    free(mfd->north_texture);
    free(mfd->south_texture);
    free(mfd->west_texture);
    free(mfd->east_texture);
}

static void grow_map(t_map_file_data *mfd, char *line)
{
    char **new_map;
    int i = 0;

    // Allocate memory for the first map line
    if (mfd->map == NULL)
    {
        mfd->map = malloc(sizeof(char *) * 2);
        if (!mfd->map)
            handle_error("Failed to allocate memory for map");
        mfd->map[0] = ft_strdup(line);
        mfd->map[1] = NULL; // Null-terminate the map array
        mfd->height = 1;    // Set map height to 1
        return;
    }

    // Allocate memory for the additional line
    new_map = malloc(sizeof(char *) * (mfd->height + 2)); // +1 for new line, +1 for NULL
    if (!new_map)
        handle_error("Failed to allocate memory for growing map");

    // Copy existing map lines
    while (i < mfd->height)
    {
        new_map[i] = mfd->map[i];
        i++;
    }

    // Add the new line and null-terminate the array
    new_map[i] = ft_strdup(line);
    if (!new_map[i])
        handle_error("Failed to duplicate map line");
    new_map[++i] = NULL;

    // Free the old map and update the pointer
    free(mfd->map);
    mfd->map = new_map;
    mfd->height++; // Increment the map height
}

// Parses an RGB color from a line and stores it in a t_color struct
void get_color(char *line, t_color *color)
{
    char *trimmed_line = skip_spaces(line);
    int i = 0;

    // Parse the red component
    color->r = ft_atoi(&trimmed_line[i]);
    // printf("red = %d\n", color->r);
    while (trimmed_line[i] && ft_isdigit(trimmed_line[i]))
        i++;
    if (trimmed_line[i++] != ',')
        handle_error("Invalid color format: expected ',' after red component");

    // Parse the green component
    trimmed_line = skip_spaces(&trimmed_line[i]);
    i = 0;
    color->g = ft_atoi(&trimmed_line[i]);
    // printf("green = %d\n", color->g);
    while (trimmed_line[i] && ft_isdigit(trimmed_line[i]))
        i++;
    if (trimmed_line[i++] != ',')
        handle_error("Invalid color format: expected ',' after green component");

    // Parse the blue component
    trimmed_line = skip_spaces(&trimmed_line[i]);
    i = 0;
    color->b = ft_atoi(&trimmed_line[i]);
    // printf("blue = %d\n", color->b);
    while (trimmed_line[i] && ft_isdigit(trimmed_line[i]))
        i++;
    // Validate that there are no trailing invalid characters
    if (!ft_strncmp(trimmed_line, "\n", 2))
        handle_error("Invalid color format: unexpected characters after blue component");

    // Ensure that the color values are within the valid range [0, 255]
    if (!check_colours_range(color))
        handle_error("Color values out of range [0-255]");
}

// Parses a configuration line for textures or colors
void parse_config_line(t_map_file_data *mfd, char *line)
{
    // Trim leading spaces
    char *trimmed_line = skip_spaces(line);

    if (ft_strncmp(trimmed_line, "NO ", 3) == 0) // North texture
        mfd->north_texture = ft_strdup(skip_spaces(&trimmed_line[3]));
    else if (ft_strncmp(trimmed_line, "SO ", 3) == 0) // South texture
        mfd->south_texture = ft_strdup(skip_spaces(&trimmed_line[3]));
    else if (ft_strncmp(trimmed_line, "WE ", 3) == 0) // West texture
        mfd->west_texture = ft_strdup(skip_spaces(&trimmed_line[3]));
    else if (ft_strncmp(trimmed_line, "EA ", 3) == 0) // East texture
        mfd->east_texture = ft_strdup(skip_spaces(&trimmed_line[3]));
    else if (ft_strncmp(trimmed_line, "F ", 2) == 0) // Floor color
    {
        mfd->floor_color = malloc(sizeof(t_color));
        if (!mfd->floor_color)
            handle_error("Failed to allocate memory for floor color");
        get_color(&trimmed_line[2], mfd->floor_color);
    }
    else if (ft_strncmp(trimmed_line, "C ", 2) == 0) // Ceiling color
    {
        mfd->ceiling_color = malloc(sizeof(t_color));
        if (!mfd->ceiling_color)
            handle_error("Failed to allocate memory for ceiling color");
        get_color(&trimmed_line[2], mfd->ceiling_color);
    }
    else
    {
        handle_error("Invalid configuration line");
    }

    // Debug print: Confirm parsed line
    // printf("Parsed config line: %s\n", trimmed_line);
}

void get_file_data(t_map_file_data *mfd, int fd)
{
    char *line;
    int map_started = 0;

    while ((line = get_next_line(fd)))
    {
        char *trimmed_line = skip_spaces(line);

        // printf("Processing line: [%s]\n", trimmed_line); // Debug print

        if (*trimmed_line == '\n') // Skip empty lines
        {
            if (map_started)
            {
                line = get_next_line(fd);
                if (line)
                    trimmed_line = skip_spaces(line);
                if (line && trimmed_line && !ft_strchr(trimmed_line, '\n'))
                {
                    free(line);
                    handle_error("Empty lines found in map section\n");
                }
            }
            free(line);
            continue;
        }

        if (is_config_line(trimmed_line) && !map_started)
        {
            parse_config_line(mfd, trimmed_line); // Parse texture/color line
        }
        else if (ft_strchr("01NSEW", *trimmed_line))
        {
            if (!map_started)
            {
                // printf("Map section starts here: [%s]\n", trimmed_line);
                map_started = 1;
            }
            grow_map(mfd, trimmed_line); // Add the line to the map
        }
        else
        {
            // printf("Error: Invalid line: [%s]\n", trimmed_line);
            handle_error("Invalid line encountered");
        }

        free(line);
    }

    if (!map_started)
        handle_error("Map section not found");
}
