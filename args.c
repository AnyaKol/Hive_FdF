/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 19:48:24 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_map(char *file, t_map *map);
static int	count_numbers(char *line);

void	check_args(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_printf(STDOUT, "Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	check_map(argv[1], map);
}

static void	check_map(char *file, t_map *map)
{
	int		fd;
	char	*line;	

	fd = open(file, O_RDONLY);
	map->cols = 0;
	map->rows = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "(null)", 6))
			break ;
		map->rows++;
		if (map->cols == 0)
			map->cols = count_numbers(line);
		if (map->cols <= 0 || map->cols != count_numbers(line))
		{
			ft_printf(STDERR, "Invalid map formatting\n");
			clean_up(line, fd);
			exit (EXIT_FAILURE);
		}
		free(line);
	}
	clean_up(line, fd);
	ft_printf(STDOUT, "Good map!\n");
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
			return (-1);
		num++;
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
	}
	return (num);
}
