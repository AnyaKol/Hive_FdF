/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/15 20:09:25 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_map(char *file, t_map *map);
static int	count_numbers(char *line);
static bool	check_atoi_zero(char *line);

void	check_args(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_printf(STDOUT, "Invalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
	check_map(argv[1], map);
}

static void	check_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	map->cols = 0;
	map->rows = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "(null)", 6))
			break ;
		map->rows++;
		count = count_numbers(line);
		if (map->cols == 0)
			map->cols = count;
		if (count == -1 || map->cols != count)
		{
			if (count != -1)
				ft_printf(STDERR, "Map is not rectangular!\n");
			clean_up(line, fd);
			exit (EXIT_FAILURE);
		}
		free(line);
	}
	clean_up(line, fd);
	if (map->rows == 0 || map->cols == 0)
	{
		ft_printf(STDERR, "Map is empty!\n");
		exit (EXIT_FAILURE);
	}
}

static int	count_numbers(char *line)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == '-' || line[i] == '+')
			i++;
		if (!ft_isdigit(line[i]))
		{
			ft_printf(STDERR, "Invalid map formatting!\n");
			return (-1);
		}
		if (ft_atoi(&line[i]) == 0 && !check_atoi_zero(&line[i]))
		{
			ft_printf(STDERR, "Int limit exceded!\n");
			return (-1);
		}
		num++;
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
	}
	return (num);
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

void	clean_up(char *line, int fd)
{
	if (line != NULL)
		free(line);
	line = NULL;
	close(fd);
}
