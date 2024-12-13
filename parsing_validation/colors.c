/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 12:04:15 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/12/13 12:40:47 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool check_color_range(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (false);
	if (color->g < 0 || color->g > 255)
		return (false);
	if (color->b < 0 || color->b > 255)
		return (false);
	return (true);
}

int verify_color(char *line, int *i)
{
	int num;
	
	skip_spaces(line, i);
	if (ft_isdigit(line[*i]) == 0)
		handle_error("Missing color");
	num = ft_atoi(&line[*i]);
	return (num);
}

void	get_color(char *line, t_color *color)
{
	int	i;

	i = 0;
	color->r = verify_color(line, &i);
	while (line && line[i] != ',')
		i++;
	i++;
	color->g = verify_color(line, &i);
	while (line && line[i] != ',')
		i++;
	i++;
	color->b = verify_color(line, &i);
}