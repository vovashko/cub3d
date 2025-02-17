/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:05:11 by pminialg      #+#    #+#                 */
/*   Updated: 2025/01/15 12:18:46 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_color_component(char *line, int *index, \
const char *component_name)
{
	int	value;

	while (line[*index] && ft_isspace(line[*index]))
		(*index)++;
	if (line[*index])
		value = ft_atoi(&line[*index]);
	else
		value = -1;
	while (line[*index] && ft_isdigit(line[*index]))
		(*index)++;
	while (line[*index] && ft_isspace(line[*index]))
		(*index)++;
	if (line[*index] == ',' && ft_strncmp(component_name, "blue", 5) != 0)
		(*index)++;
	else if (ft_strncmp(component_name, "blue", 5) != 0)
		handle_error("Invalid color format. Expected , as separator.");
	return (value);
}

static void	validate_color_component(char *line, int *color, \
const char *component_name, int *index)
{
	if (*color == -1)
	{
		*color = parse_color_component(line, index, component_name);
	}
}

static void	validate_colors(t_color *color, char *line)
{
	int	index;

	index = 0;
	validate_color_component(line, &color->r, "red", &index);
	validate_color_component(line, &color->g, "green", &index);
	validate_color_component(line, &color->b, "blue", &index);
}

void	get_color(char *line, t_color *color)
{
	validate_colors(color, line);
	if (!check_colours_range(color))
		handle_error("Color values out of range [0-255]");
}

// Validate colours range
bool	check_colours_range(t_color *color)
{
	if (color == NULL)
		return (false);
	if (color->r < 0 || color->r > 255)
		return (false);
	if (color->g < 0 || color->g > 255)
		return (false);
	if (color->b < 0 || color->b > 255)
		return (false);
	return (true);
}
