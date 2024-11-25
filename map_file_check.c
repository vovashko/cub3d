/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_file_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:46:49 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/11/25 14:00:44 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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


// bool check_file_content(char *file)
// {
// 	int fd;
	
// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		return (false);

// 	// check if the file is empty
// 	if (read(fd, NULL, 0) == 0)
// 	{
// 		close(fd);
// 		return (false);
// 	}
	
// }