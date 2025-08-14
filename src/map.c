/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:29 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/14 19:37:49 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_map(t_map *map);
static void	fill_row(int *row, char *line, int cols, int *peak);

void	fill_map(char *file, t_map *map)
{
	int		i;
	char	*line;
	int		fd;

	create_map(map);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < map->rows)
	{
		line = get_next_line(fd);
		fill_row(map->values[i], line, map->cols, &map->peak);
		free(line);
		i++;
	}
	close(fd);
	set_map_rotation(map, M_PI / 6.0, M_PI / 6.0);
}

static void	create_map(t_map *map)
{
	int	i;

	map->values = ft_calloc(map->rows + 1, sizeof(int *));
	if (map->values == NULL)
	{
		ft_printf(STDERR, "Map allocation error\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < map->rows)
	{
		map->values[i] = ft_calloc(map->cols + 1, sizeof(int));
		if (map->values[i] == NULL)
		{
			free_map(map);
			ft_printf(STDERR, "Map allocation error\n");
			exit (EXIT_FAILURE);
		}
		i++;
	}
	map->peak = INT_MIN;
}

static void	fill_row(int *row, char *line, int cols, int *peak)
{
	int		i;
	int		line_i;
	
	i = 0;
	line_i = 0;
	while (i < cols)
	{
		if (ft_isdigit(line[line_i]) || line[line_i] == '-')
		{
			row[i] = ft_atoi(&line[line_i]);
			if (row[i] > *peak)
				*peak = row[i];
			i++;
			if (line[line_i] == '-')
				line_i++;
			while (ft_isdigit(line[line_i]))
				line_i++;
		}
		line_i++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (map->values == NULL)
		return ;
	i = 0;
	while (i < map->rows && map->values[i] != NULL)
	{
		free(map->values[i]);
		map->values[i] = NULL;
		i++;
	}
	free(map->values);
	map->values = NULL;
}
