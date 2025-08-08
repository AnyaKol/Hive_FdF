/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/08 19:26:11 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_args(int argc, char **argv);
int		count_numbers(char *line);

int	main(int argc, char **argv)
{
	static mlx_image_t	*image;
	mlx_t	*mlx;

	check_args(argc, argv);
	ft_printf("Good map!\n");
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	image = mlx_new_image(mlx, 128, 128);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

void	check_args(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		num;

	if (argc != 2)
	{
		ft_printf("Invalid number of arguments\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	num = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "(null)", 6))
			break ;
		if (num == 0)
			num = count_numbers(line);
		if (num <= 0 || num != count_numbers(line))
		{
			ft_printf("Invalid map formatting\n");
			free(line);
			line = NULL;
			close(fd);
			exit (1);
		}
		free(line);
	}
	free(line);
	line = NULL;
	close(fd);
}

int	count_numbers(char *line)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == '-')
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
