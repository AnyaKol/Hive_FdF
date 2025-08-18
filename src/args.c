/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/18 17:46:41 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_map(char *file, t_map *map);
static int	count_numbers(char *line);
static int	check_count(int *cols, int count);

void	check_args(int argc, char **argv, t_map *map)
{
	if (argc != 2)
		print_error_and_exit("Invalid number of arguments!\n");
	map->cols = 0;
	map->rows = 0;
	check_map(argv[1], map);
}

static void	check_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "(null)", 6))
			break ;
		map->rows++;
		count = count_numbers(line);
		if (check_count(&map->cols, count) == ERROR)
		{
			clean_up(line, fd);
			exit (EXIT_FAILURE);
		}
		free(line);
	}
	clean_up(line, fd);
	if (map->rows == 0 || map->cols == 0)
		print_error_and_exit("Map is empty!\n");
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
			return (print_error_and_return("Invalid map formatting!\n"));
		if (ft_atoi(&line[i]) == 0 && line[i] != '0')
			return (print_error_and_return("Int limit exceded!\n"));
		num++;
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
	}
	return (num);
}

static int	check_count(int *cols, int count)
{
	if (count == ERROR)
		return (ERROR);
	if (*cols == 0)
		*cols = count;
	if (*cols != count)
		return (print_error_and_return("Map is not rectangular!\n"));
	return (SUCCESS);
}

void	clean_up(char *line, int fd)
{
	if (line != NULL)
		free(line);
	line = NULL;
	close(fd);
}
