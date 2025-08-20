/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 11:52:31 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_sign(int num)
{
	return ((num > 0) - (num < 0));
}

int	get_last_byte(int num)
{
	return (num & 0x0000FF);
}

void	clean_up(char *line, int fd)
{
	if (line != NULL)
		free(line);
	line = NULL;
	close(fd);
}

void	check_fd(int fd)
{
	if (fd < 0)
		print_error_and_exit("Failed to open file\n");
}

void	check_line(char *line, int fd, t_map *map)
{
	if (line == NULL)
	{
		close(fd);
		free_map(map);
	}
}
