/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:29 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/18 19:52:32 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	create_map(int ***values, t_map *map);
static void	fill_row(t_map *map, int row, char *line);
static void	free_arr(int **values, int rows);

void	fill_map(char *file, t_map *map)
{
	int		i;
	char	*line;
	int		fd;

	if (create_map(&map->values, map) == ERROR
		|| create_map(&map->colors, map) == ERROR)
	{
		free_map(map);
		exit(ERROR);
	}
	map->peak = 0;
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < map->rows)
	{
		line = get_next_line(fd);
		fill_row(map, i, line);
		free(line);
		i++;
	}
	close(fd);
	set_map_rotation(map, M_PI / 6.0, M_PI / 6.0);
	set_map_zoom(map, 100);
}

static int	create_map(int ***values, t_map *map)
{
	int	i;

	*values = ft_calloc(map->rows + 1, sizeof(int *));
	if (*values == NULL)
		return (print_error_and_return("Map allocation error\n"));
	i = 0;
	while (i < map->rows)
	{
		(*values)[i] = ft_calloc(map->cols + 1, sizeof(int));
		if ((*values)[i] == NULL)
		{
			free_map(map);
			return (print_error_and_return("Map allocation error\n"));
		}
		i++;
	}
	return (SUCCESS);
}

static void	fill_row(t_map *map, int row, char *line)
{
	int		col;
	int		i;

	col = 0;
	i = 0;
	while (col < map->cols)
	{
		if (ft_isdigit(line[i]) || line[i] == '-')
		{
			map->values[row][col] = ft_atoi(&line[i]);
			if (abs(map->values[row][col]) > abs(map->peak))
				map->peak = map->values[row][col];
			col++;
			if (line[i] == '-')
				i++;
			while (ft_isdigit(line[i]))
				i++;
			if (!ft_strncmp(&line[i], ",0x", 3))
				map->colors[row][col] = ft_atoi_base(&line[i + 3], BASE_HEX);
			i += skip_color(&line[i]);
		}
		i++;
	}
}

void	free_map(t_map *map)
{
	free_arr(map->values, map->rows);
	free_arr(map->colors, map->rows);
}

static void	free_arr(int **values, int rows)
{
	int	i;

	if (values == NULL)
		return ;
	i = 0;
	while (i < rows && values[i] != NULL)
	{
		free(values[i]);
		values[i] = NULL;
		i++;
	}
	free(values);
	values = NULL;
}
