/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:29 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/12 14:48:32 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_map(t_map *map);
static bool	fill_row(int *row, char *line, int cols);
static bool	check_atoi_zero(char *line);

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
		if (!ft_strncmp(line, "(null)", 6))
			break ;
		if (!fill_row(map->values[i], line, map->cols))
		{
			free_map(map);
			clean_up(line, fd);
			ft_printf(STDERR, "Int limit exceded\n");
			exit (EXIT_FAILURE);
		}
		free(line);
		i++;
	}
	close(fd);
	ft_printf(STDOUT, "Map created!\n");
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
}

static bool	fill_row(int *row, char *line, int cols)
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
			if (row[i] == 0 && !check_atoi_zero(&line[line_i]))
				return (false);
			i++;
			if (line[line_i] == '-')
				line_i++;
			while (ft_isdigit(line[line_i]))
				line_i++;
		}
		line_i++;
	}
	return (true);
}

static bool	check_atoi_zero(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (line[i] == '0')
		i++;
	if (ft_isdigit(line[i]))
		return (false);
	return (true);
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
